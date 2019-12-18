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
typedef  int u8 ;
typedef  int u32 ;
struct ecore_ptt {int dummy; } ;
struct ecore_hwfn {int /*<<< orphan*/  p_dev; } ;
typedef  enum _ecore_status_t { ____Placeholder__ecore_status_t } _ecore_status_t ;

/* Variables and functions */
 int /*<<< orphan*/  DB_REC_REAL_DEAL ; 
 int /*<<< orphan*/  DORQ_REG_DPM_FORCE_ABORT ; 
 int /*<<< orphan*/  DORQ_REG_PF_OVFL_STICKY ; 
 int /*<<< orphan*/  DORQ_REG_PF_USAGE_CNT ; 
 int /*<<< orphan*/  DP_NOTICE (int /*<<< orphan*/ ,int,char*,int,int) ; 
 int ECORE_DB_REC_COUNT ; 
 int ECORE_DB_REC_INTERVAL ; 
 int ECORE_SUCCESS ; 
 int ECORE_TIMEOUT ; 
 int /*<<< orphan*/  OSAL_UDELAY (int) ; 
 int /*<<< orphan*/  ecore_db_recovery_execute (struct ecore_hwfn*,int /*<<< orphan*/ ) ; 
 int ecore_rd (struct ecore_hwfn*,struct ecore_ptt*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ecore_wr (struct ecore_hwfn*,struct ecore_ptt*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static enum _ecore_status_t ecore_db_rec_attn(struct ecore_hwfn *p_hwfn,
					      struct ecore_ptt *p_ptt)
{
	u8 count = ECORE_DB_REC_COUNT;
	u32 usage = 1;

	/* wait for usage to zero or count to run out. This is necessary since
	 * EDPM doorbell transactions can take multiple 64b cycles, and as such
	 * can "split" over the pci. Possibly, the doorbell drop can happen with
	 * half an EDPM in the queue and other half dropped. Another EDPM
	 * doorbell to the same address (from doorbell recovery mechanism or
	 * from the doorbelling entity) could have first half dropped and second
	 * half interperted as continuation of the first. To prevent such
	 * malformed doorbells from reaching the device, flush the queue before
	 * releaseing the overflow sticky indication.
	 */
	while (count-- && usage) {
		usage = ecore_rd(p_hwfn, p_ptt, DORQ_REG_PF_USAGE_CNT);
		OSAL_UDELAY(ECORE_DB_REC_INTERVAL);
	}

	/* should have been depleted by now */
	if (usage) {
		DP_NOTICE(p_hwfn->p_dev, false,
			  "DB recovery: doorbell usage failed to zero after %d usec. usage was %x\n",
			  ECORE_DB_REC_INTERVAL * ECORE_DB_REC_COUNT, usage);
		return ECORE_TIMEOUT;
	}

	/* flush any pedning (e)dpm as they may never arrive */
	ecore_wr(p_hwfn, p_ptt, DORQ_REG_DPM_FORCE_ABORT, 0x1);

	/* release overflow sticky indication (stop silently dropping everything) */
	ecore_wr(p_hwfn, p_ptt, DORQ_REG_PF_OVFL_STICKY, 0x0);

	/* repeat all last doorbells (doorbell drop recovery) */
	ecore_db_recovery_execute(p_hwfn, DB_REC_REAL_DEAL);

	return ECORE_SUCCESS;
}