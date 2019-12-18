#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint8_t ;
typedef  int uint32_t ;
typedef  int /*<<< orphan*/  t_Error ;
struct TYPE_7__ {int flags; int /*<<< orphan*/  p_BmPortalLow; int /*<<< orphan*/  irq; int /*<<< orphan*/  depletionPoolsTable; scalar_t__ rcrCons; scalar_t__ rcrProd; scalar_t__ slowpoll; struct bman_depletion* pools; TYPE_1__* cbs; } ;
typedef  TYPE_2__ t_BmPortal ;
struct bman_depletion {int dummy; } ;
typedef  int e_BmPortalRcrConsumeMode ;
typedef  int e_BmPortalProduceMode ;
struct TYPE_6__ {int /*<<< orphan*/ * f_BmPrefetchCb; int /*<<< orphan*/  f_BmUpdateCb; int /*<<< orphan*/  f_BmCommitCb; } ;

/* Variables and functions */
 int BMAN_PORTAL_FLAG_CACHE ; 
 int BMAN_PORTAL_FLAG_IRQ ; 
 int BMAN_PORTAL_FLAG_RECOVER ; 
 int BMAN_PORTAL_FLAG_WAIT ; 
 scalar_t__ BM_MAX_NUM_OF_POOLS ; 
 int BM_PIRQ_BSCN ; 
 int BM_PIRQ_RCRI ; 
 size_t BM_RCR_RING ; 
 int /*<<< orphan*/  ERROR_CODE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  E_INVALID_STATE ; 
 int /*<<< orphan*/  E_OK ; 
 int /*<<< orphan*/  MAJOR ; 
 int /*<<< orphan*/  REPORT_ERROR (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  XX_EnableIntr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XX_Free (TYPE_2__*) ; 
 int /*<<< orphan*/  XX_SetIntr (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  bm_isr_bscn_mask (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bm_isr_disable_write (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  bm_isr_enable_write (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  bm_isr_status_clear (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  bm_isr_uninhibit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bm_mc_finish (int /*<<< orphan*/ ) ; 
 scalar_t__ bm_mc_init (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * bm_rcr_cce_prefetch ; 
 int /*<<< orphan*/  bm_rcr_cce_update ; 
 int /*<<< orphan*/  bm_rcr_cci_update ; 
 int /*<<< orphan*/  bm_rcr_finish (int /*<<< orphan*/ ) ; 
 int bm_rcr_get_fill (int /*<<< orphan*/ ) ; 
 scalar_t__ bm_rcr_init (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  bm_rcr_pce_commit ; 
 int /*<<< orphan*/  bm_rcr_pci_commit ; 
 int /*<<< orphan*/  bm_rcr_pvb_commit ; 
 int /*<<< orphan*/  bman_depletion_init (struct bman_depletion*) ; 
#define  e_BmPortalPCE 132 
#define  e_BmPortalPCI 131 
#define  e_BmPortalPVB 130 
#define  e_BmPortalRcrCCE 129 
#define  e_BmPortalRcrCCI 128 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  portal_isr ; 

__attribute__((used)) static t_Error bman_create_portal(t_BmPortal *p_BmPortal,
                                  uint32_t flags,
                                  const struct bman_depletion *pools)
{
    int                             ret = 0;
    uint8_t                         bpid = 0;
    e_BmPortalRcrConsumeMode        rcr_cmode;
    e_BmPortalProduceMode           pmode;

    pmode     = e_BmPortalPVB;
    rcr_cmode = (flags & BMAN_PORTAL_FLAG_CACHE) ? e_BmPortalRcrCCE : e_BmPortalRcrCCI;

    switch (pmode)
    {
        case e_BmPortalPCI:
            p_BmPortal->cbs[BM_RCR_RING].f_BmCommitCb = bm_rcr_pci_commit;
            break;
        case e_BmPortalPCE:
            p_BmPortal->cbs[BM_RCR_RING].f_BmCommitCb = bm_rcr_pce_commit;
            break;
        case e_BmPortalPVB:
            p_BmPortal->cbs[BM_RCR_RING].f_BmCommitCb = bm_rcr_pvb_commit;
            break;
    }
    switch (rcr_cmode)
    {
        case e_BmPortalRcrCCI:
            p_BmPortal->cbs[BM_RCR_RING].f_BmUpdateCb      = bm_rcr_cci_update;
            p_BmPortal->cbs[BM_RCR_RING].f_BmPrefetchCb    = NULL;
            break;
        case e_BmPortalRcrCCE:
            p_BmPortal->cbs[BM_RCR_RING].f_BmUpdateCb      = bm_rcr_cce_update;
            p_BmPortal->cbs[BM_RCR_RING].f_BmPrefetchCb    = bm_rcr_cce_prefetch;
            break;
    }

    if (bm_rcr_init(p_BmPortal->p_BmPortalLow, pmode, rcr_cmode)) {
        REPORT_ERROR(MAJOR, E_INVALID_STATE, ("RCR initialization failed"));
        goto fail_rcr;
    }
    if (bm_mc_init(p_BmPortal->p_BmPortalLow)) {
        REPORT_ERROR(MAJOR, E_INVALID_STATE, ("MC initialization failed"));
        goto fail_mc;
    }
    p_BmPortal->pools[0] = *pools;
    bman_depletion_init(&p_BmPortal->pools[1]);
    while (bpid < BM_MAX_NUM_OF_POOLS) {
        /* Default to all BPIDs disabled, we enable as required
         * at run-time. */
        bm_isr_bscn_mask(p_BmPortal->p_BmPortalLow, bpid, 0);
        bpid++;
    }
    p_BmPortal->flags = flags;
    p_BmPortal->slowpoll = 0;
    p_BmPortal->rcrProd = p_BmPortal->rcrCons = 0;
    memset(&p_BmPortal->depletionPoolsTable, 0, sizeof(p_BmPortal->depletionPoolsTable));
    /* Write-to-clear any stale interrupt status bits */
    bm_isr_disable_write(p_BmPortal->p_BmPortalLow, 0xffffffff);
    bm_isr_status_clear(p_BmPortal->p_BmPortalLow, 0xffffffff);
    bm_isr_enable_write(p_BmPortal->p_BmPortalLow, BM_PIRQ_RCRI | BM_PIRQ_BSCN);
    if (flags & BMAN_PORTAL_FLAG_IRQ)
    {
        XX_SetIntr(p_BmPortal->irq, portal_isr, p_BmPortal);
        XX_EnableIntr(p_BmPortal->irq);
        /* Enable the bits that make sense */
        bm_isr_uninhibit(p_BmPortal->p_BmPortalLow);
    } else
        /* without IRQ, we can't block */
        flags &= ~BMAN_PORTAL_FLAG_WAIT;
    /* Need RCR to be empty before continuing */
    bm_isr_disable_write(p_BmPortal->p_BmPortalLow, (uint32_t)~BM_PIRQ_RCRI);
    if (!(flags & BMAN_PORTAL_FLAG_RECOVER) ||
        !(flags & BMAN_PORTAL_FLAG_WAIT))
        ret = bm_rcr_get_fill(p_BmPortal->p_BmPortalLow);
    if (ret) {
        REPORT_ERROR(MAJOR, E_INVALID_STATE, ("RCR unclean, need recovery"));
        goto fail_rcr_empty;
    }
    bm_isr_disable_write(p_BmPortal->p_BmPortalLow, 0);
    return E_OK;
fail_rcr_empty:
    bm_mc_finish(p_BmPortal->p_BmPortalLow);
fail_mc:
    bm_rcr_finish(p_BmPortal->p_BmPortalLow);
fail_rcr:
    XX_Free(p_BmPortal);
    return ERROR_CODE(E_INVALID_STATE);
}