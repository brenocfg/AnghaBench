#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int u32 ;
struct ecore_ptt {int dummy; } ;
struct ecore_hwfn {int /*<<< orphan*/  p_dev; struct ecore_ptt* p_dpc_ptt; } ;
typedef  enum _ecore_status_t { ____Placeholder__ecore_status_t } _ecore_status_t ;

/* Variables and functions */
 int /*<<< orphan*/  DORQ_REG_DB_DROP_DETAILS ; 
 int /*<<< orphan*/  DORQ_REG_DB_DROP_DETAILS_ADDRESS ; 
 int /*<<< orphan*/  DORQ_REG_DB_DROP_DETAILS_REASON ; 
 int /*<<< orphan*/  DORQ_REG_DB_DROP_DETAILS_REL ; 
 int /*<<< orphan*/  DORQ_REG_DB_DROP_REASON ; 
 int /*<<< orphan*/  DORQ_REG_INT_STS ; 
 int DORQ_REG_INT_STS_DB_DROP ; 
 int DORQ_REG_INT_STS_DORQ_FIFO_AFULL ; 
 int DORQ_REG_INT_STS_DORQ_FIFO_OVFL_ERR ; 
 int /*<<< orphan*/  DORQ_REG_INT_STS_WR ; 
 int /*<<< orphan*/  DORQ_REG_PF_OVFL_STICKY ; 
 int /*<<< orphan*/  DP_INFO (struct ecore_hwfn*,char*) ; 
 int /*<<< orphan*/  DP_NOTICE (int /*<<< orphan*/ ,int,char*,int,...) ; 
 int /*<<< orphan*/  ECORE_DORQ_ATTENTION_OPAQUE ; 
 int ECORE_DORQ_ATTENTION_REASON_MASK ; 
 int /*<<< orphan*/  ECORE_DORQ_ATTENTION_SIZE ; 
 int ECORE_INVAL ; 
 int ECORE_SUCCESS ; 
 int GET_FIELD (int,int /*<<< orphan*/ ) ; 
 int ecore_db_rec_attn (struct ecore_hwfn*,struct ecore_ptt*) ; 
 int ecore_rd (struct ecore_hwfn*,struct ecore_ptt*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ecore_wr (struct ecore_hwfn*,struct ecore_ptt*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static enum _ecore_status_t ecore_dorq_attn_cb(struct ecore_hwfn *p_hwfn)
{
	u32 int_sts, first_drop_reason, details, address, overflow,
		all_drops_reason;
	struct ecore_ptt *p_ptt = p_hwfn->p_dpc_ptt;
	enum _ecore_status_t rc;

	int_sts = ecore_rd(p_hwfn, p_ptt, DORQ_REG_INT_STS);
	DP_NOTICE(p_hwfn->p_dev, false, "DORQ attention. int_sts was %x\n",
		  int_sts);

	/* int_sts may be zero since all PFs were interrupted for doorbell
	 * overflow but another one already handled it. Can abort here. If
	 * This PF also requires overflow recovery we will be interrupted again.
	 * The masked almost full indication may also be set. Ignoring.
	 */
	if (!(int_sts & ~DORQ_REG_INT_STS_DORQ_FIFO_AFULL))
		return ECORE_SUCCESS;

	/* check if db_drop or overflow happened */
	if (int_sts & (DORQ_REG_INT_STS_DB_DROP |
		       DORQ_REG_INT_STS_DORQ_FIFO_OVFL_ERR)) {
	
		/* obtain data about db drop/overflow */
		first_drop_reason = ecore_rd(p_hwfn, p_ptt,
				  DORQ_REG_DB_DROP_REASON) &
				  ECORE_DORQ_ATTENTION_REASON_MASK;
		details = ecore_rd(p_hwfn, p_ptt,
				   DORQ_REG_DB_DROP_DETAILS);
		address = ecore_rd(p_hwfn, p_ptt,
				   DORQ_REG_DB_DROP_DETAILS_ADDRESS);
		overflow = ecore_rd(p_hwfn, p_ptt,
				    DORQ_REG_PF_OVFL_STICKY);
		all_drops_reason = ecore_rd(p_hwfn, p_ptt,
					    DORQ_REG_DB_DROP_DETAILS_REASON);

		/* log info */
		DP_NOTICE(p_hwfn->p_dev, false,
			  "Doorbell drop occurred\n"
			  "Address\t\t0x%08x\t(second BAR address)\n"
			  "FID\t\t0x%04x\t\t(Opaque FID)\n"
			  "Size\t\t0x%04x\t\t(in bytes)\n"
			  "1st drop reason\t0x%08x\t(details on first drop since last handling)\n"
			  "Sticky reasons\t0x%08x\t(all drop reasons since last handling)\n"
			  "Overflow\t0x%x\t\t(a per PF indication)\n",
			  address, GET_FIELD(details, ECORE_DORQ_ATTENTION_OPAQUE),
			  GET_FIELD(details, ECORE_DORQ_ATTENTION_SIZE) * 4,
			  first_drop_reason, all_drops_reason, overflow);

		/* if this PF caused overflow, initiate recovery */
		if (overflow) {
			rc = ecore_db_rec_attn(p_hwfn, p_ptt);
			if (rc != ECORE_SUCCESS)
				return rc;
		}

		/* clear the doorbell drop details and prepare for next drop */
		ecore_wr(p_hwfn, p_ptt, DORQ_REG_DB_DROP_DETAILS_REL, 0);

		/* mark interrupt as handeld (note: even if drop was due to a diffrent
		 * reason than overflow we mark as handled)
		 */
		ecore_wr(p_hwfn, p_ptt, DORQ_REG_INT_STS_WR,
			 DORQ_REG_INT_STS_DB_DROP | DORQ_REG_INT_STS_DORQ_FIFO_OVFL_ERR);

		/* if there are no indications otherthan drop indications, success */
		if ((int_sts & ~(DORQ_REG_INT_STS_DB_DROP |
				 DORQ_REG_INT_STS_DORQ_FIFO_OVFL_ERR |
				 DORQ_REG_INT_STS_DORQ_FIFO_AFULL)) == 0)
			return ECORE_SUCCESS;
	}

	/* some other indication was present - non recoverable */
	DP_INFO(p_hwfn, "DORQ fatal attention\n");

	return ECORE_INVAL;
}