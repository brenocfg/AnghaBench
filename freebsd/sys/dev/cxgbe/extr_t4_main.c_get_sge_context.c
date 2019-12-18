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
struct t4_sge_context {scalar_t__ cid; scalar_t__ mem_id; int /*<<< orphan*/ * data; } ;
struct adapter {int flags; int /*<<< orphan*/  mbox; } ;

/* Variables and functions */
 scalar_t__ CTXT_CNM ; 
 scalar_t__ CTXT_EGRESS ; 
 scalar_t__ CTXT_FLM ; 
 scalar_t__ CTXT_INGRESS ; 
 int EINVAL ; 
 int FW_OK ; 
 int INTR_OK ; 
 scalar_t__ M_CTXTQID ; 
 int SLEEP_OK ; 
 int begin_synchronized_op (struct adapter*,int /*<<< orphan*/ *,int,char*) ; 
 int /*<<< orphan*/  end_synchronized_op (struct adapter*,int /*<<< orphan*/ ) ; 
 int t4_sge_ctxt_rd (struct adapter*,int /*<<< orphan*/ ,scalar_t__,scalar_t__,int /*<<< orphan*/ *) ; 
 int t4_sge_ctxt_rd_bd (struct adapter*,scalar_t__,scalar_t__,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
get_sge_context(struct adapter *sc, struct t4_sge_context *cntxt)
{
	int rc;

	if (cntxt->cid > M_CTXTQID)
		return (EINVAL);

	if (cntxt->mem_id != CTXT_EGRESS && cntxt->mem_id != CTXT_INGRESS &&
	    cntxt->mem_id != CTXT_FLM && cntxt->mem_id != CTXT_CNM)
		return (EINVAL);

	rc = begin_synchronized_op(sc, NULL, SLEEP_OK | INTR_OK, "t4ctxt");
	if (rc)
		return (rc);

	if (sc->flags & FW_OK) {
		rc = -t4_sge_ctxt_rd(sc, sc->mbox, cntxt->cid, cntxt->mem_id,
		    &cntxt->data[0]);
		if (rc == 0)
			goto done;
	}

	/*
	 * Read via firmware failed or wasn't even attempted.  Read directly via
	 * the backdoor.
	 */
	rc = -t4_sge_ctxt_rd_bd(sc, cntxt->cid, cntxt->mem_id, &cntxt->data[0]);
done:
	end_synchronized_op(sc, 0);
	return (rc);
}