#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_5__ ;
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_2__* tcb_p ;
typedef  TYPE_3__* lcb_p ;
typedef  TYPE_4__* hcb_p ;
typedef  TYPE_5__* ccb_p ;
struct TYPE_17__ {size_t target; int tag; int /*<<< orphan*/  link_ccbq; int /*<<< orphan*/  host_status; int /*<<< orphan*/ * cam_ccb; scalar_t__ dmamapped; int /*<<< orphan*/  dmamap; int /*<<< orphan*/  lun; } ;
struct TYPE_16__ {int /*<<< orphan*/  free_ccbq; int /*<<< orphan*/  data_dmat; TYPE_5__* last_cp; int /*<<< orphan*/  bad_itl_ba; int /*<<< orphan*/  bad_itlq_ba; TYPE_2__* target; } ;
struct TYPE_13__ {void* resel_sa; void* itl_task_sa; } ;
struct TYPE_15__ {int* cb_tags; size_t if_tag; scalar_t__ busy_itlq; scalar_t__ busy_itl; TYPE_1__ head; void** itlq_tbl; } ;
struct TYPE_14__ {TYPE_5__* nego_cp; int /*<<< orphan*/  busy0_map; } ;

/* Variables and functions */
 int DEBUG_FLAGS ; 
 int DEBUG_TAGS ; 
 int /*<<< orphan*/  HS_IDLE ; 
 int NO_TAG ; 
 int /*<<< orphan*/  PRINT_LUN (TYPE_4__*,size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SCRIPTB_BA (TYPE_4__*,int /*<<< orphan*/ ) ; 
 size_t SYM_CONF_MAX_TASK ; 
 int /*<<< orphan*/  bus_dmamap_unload (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 void* cpu_to_scr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*,TYPE_5__*,int) ; 
 int /*<<< orphan*/  resel_bad_lun ; 
 int /*<<< orphan*/  sym_clr_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sym_insque_head (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 TYPE_3__* sym_lp (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sym_remque (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void sym_free_ccb(hcb_p np, ccb_p cp)
{
	tcb_p tp = &np->target[cp->target];
	lcb_p lp = sym_lp(tp, cp->lun);

	if (DEBUG_FLAGS & DEBUG_TAGS) {
		PRINT_LUN(np, cp->target, cp->lun);
		printf ("ccb @%p freeing tag %d.\n", cp, cp->tag);
	}

	/*
	 *  If LCB available,
	 */
	if (lp) {
		/*
		 *  If tagged, release the tag, set the relect path
		 */
		if (cp->tag != NO_TAG) {
			/*
			 *  Free the tag value.
			 */
			lp->cb_tags[lp->if_tag] = cp->tag;
			if (++lp->if_tag == SYM_CONF_MAX_TASK)
				lp->if_tag = 0;
			/*
			 *  Make the reselect path invalid,
			 *  and uncount this CCB.
			 */
			lp->itlq_tbl[cp->tag] = cpu_to_scr(np->bad_itlq_ba);
			--lp->busy_itlq;
		} else {	/* Untagged */
			/*
			 *  Make the reselect path invalid,
			 *  and uncount this CCB.
			 */
			lp->head.itl_task_sa = cpu_to_scr(np->bad_itl_ba);
			--lp->busy_itl;
		}
		/*
		 *  If no JOB active, make the LUN reselect path invalid.
		 */
		if (lp->busy_itlq == 0 && lp->busy_itl == 0)
			lp->head.resel_sa =
				cpu_to_scr(SCRIPTB_BA (np, resel_bad_lun));
	}
	/*
	 *  Otherwise, we only accept 1 IO per LUN.
	 *  Clear the bit that keeps track of this IO.
	 */
	else
		sym_clr_bit(tp->busy0_map, cp->lun);

	/*
	 *  We donnot queue more than 1 ccb per target
	 *  with negotiation at any time. If this ccb was
	 *  used for negotiation, clear this info in the tcb.
	 */
	if (cp == tp->nego_cp)
		tp->nego_cp = NULL;

#ifdef SYM_CONF_IARB_SUPPORT
	/*
	 *  If we just complete the last queued CCB,
	 *  clear this info that is no longer relevant.
	 */
	if (cp == np->last_cp)
		np->last_cp = NULL;
#endif

	/*
	 *  Unmap user data from DMA map if needed.
	 */
	if (cp->dmamapped) {
		bus_dmamap_unload(np->data_dmat, cp->dmamap);
		cp->dmamapped = 0;
	}

	/*
	 *  Make this CCB available.
	 */
	cp->cam_ccb = NULL;
	cp->host_status = HS_IDLE;
	sym_remque(&cp->link_ccbq);
	sym_insque_head(&cp->link_ccbq, &np->free_ccbq);
}