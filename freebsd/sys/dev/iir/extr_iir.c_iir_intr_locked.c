#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_9__ ;
typedef  struct TYPE_17__   TYPE_7__ ;
typedef  struct TYPE_16__   TYPE_6__ ;
typedef  struct TYPE_15__   TYPE_5__ ;
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  int u_int32_t ;
struct TYPE_11__ {int index; int /*<<< orphan*/  ionode; } ;
struct TYPE_12__ {TYPE_1__ driver; } ;
struct TYPE_18__ {int size; TYPE_2__ eu; } ;
struct gdt_softc {int sc_state; int (* sc_get_status ) (struct gdt_softc*) ;int /*<<< orphan*/  sc_info; int /*<<< orphan*/  sc_status; int /*<<< orphan*/  sc_ucmd_queue; TYPE_9__ sc_dvr; int /*<<< orphan*/  sc_hanum; int /*<<< orphan*/  sc_devnode; struct gdt_ccb* sc_gccbs; int /*<<< orphan*/  sc_info2; int /*<<< orphan*/  sc_service; int /*<<< orphan*/  (* sc_intr ) (struct gdt_softc*,struct gdt_intr_ctx*) ;int /*<<< orphan*/  sc_lock; } ;
struct gdt_intr_ctx {int istatus; int /*<<< orphan*/  service; int /*<<< orphan*/  info2; int /*<<< orphan*/  info; int /*<<< orphan*/  cmd_status; } ;
struct gdt_ccb {int gc_flags; int /*<<< orphan*/  gc_scratch; TYPE_7__* gc_ucmd; int /*<<< orphan*/  gc_service; } ;
struct TYPE_15__ {int sdlen; int /*<<< orphan*/  sense_len; } ;
struct TYPE_14__ {int BlockCnt; } ;
struct TYPE_13__ {int param_size; } ;
struct TYPE_16__ {TYPE_5__ raw; TYPE_4__ cache; TYPE_3__ ioctl; } ;
struct TYPE_17__ {int /*<<< orphan*/  data; TYPE_6__ u; int /*<<< orphan*/  OpCode; int /*<<< orphan*/  service; int /*<<< orphan*/  complete_flag; int /*<<< orphan*/  info; int /*<<< orphan*/  status; } ;
typedef  TYPE_7__ gdt_ucmd_t ;

/* Variables and functions */
 int GDT_ASYNCINDEX ; 
 int /*<<< orphan*/  GDT_CACHESERVICE ; 
 int /*<<< orphan*/  GDT_DPRINTF (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  GDT_D_DEBUG ; 
 int /*<<< orphan*/  GDT_D_INTR ; 
 int /*<<< orphan*/  GDT_D_INVALID ; 
 int /*<<< orphan*/  GDT_ES_DRIVER ; 
#define  GDT_GCF_INTERNAL 130 
#define  GDT_GCF_IOCTL 129 
#define  GDT_GCF_UNUSED 128 
 int /*<<< orphan*/  GDT_IOCTL ; 
 int GDT_POLLING ; 
 int GDT_POLL_WAIT ; 
 int GDT_SECTOR_SIZE ; 
 int GDT_SPEZINDEX ; 
 int /*<<< orphan*/  GDT_S_BSY ; 
 int /*<<< orphan*/  GDT_S_NO_STATUS ; 
 int /*<<< orphan*/  MA_OWNED ; 
 int /*<<< orphan*/  TAILQ_INSERT_HEAD (int /*<<< orphan*/ *,TYPE_7__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  bcopy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  device_get_nameunit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gdt_async_event (struct gdt_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gdt_free_ccb (struct gdt_softc*,struct gdt_ccb*) ; 
 int /*<<< orphan*/  gdt_next (struct gdt_softc*) ; 
 int /*<<< orphan*/  gdt_store_event (int /*<<< orphan*/ ,int,TYPE_9__*) ; 
 int /*<<< orphan*/  gdt_sync_event (struct gdt_softc*,int /*<<< orphan*/ ,int,struct gdt_ccb*) ; 
 int /*<<< orphan*/  links ; 
 int /*<<< orphan*/  mtx_assert (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int stub1 (struct gdt_softc*) ; 
 int /*<<< orphan*/  stub2 (struct gdt_softc*,struct gdt_intr_ctx*) ; 
 int /*<<< orphan*/  wakeup (TYPE_7__*) ; 

int
iir_intr_locked(struct gdt_softc *gdt)
{
    struct gdt_intr_ctx ctx;
    struct gdt_ccb *gccb;
    gdt_ucmd_t *ucmd;
    u_int32_t cnt;

    GDT_DPRINTF(GDT_D_INTR, ("gdt_intr(%p)\n", gdt));

    mtx_assert(&gdt->sc_lock, MA_OWNED);

    /* If polling and we were not called from gdt_wait, just return */
    if ((gdt->sc_state & GDT_POLLING) &&
        !(gdt->sc_state & GDT_POLL_WAIT))
        return (0);

    ctx.istatus = gdt->sc_get_status(gdt);
    if (ctx.istatus == 0x00) {
        gdt->sc_status = GDT_S_NO_STATUS;
        return (ctx.istatus);
    }

    gdt->sc_intr(gdt, &ctx);

    gdt->sc_status = ctx.cmd_status;
    gdt->sc_service = ctx.service;
    gdt->sc_info = ctx.info;
    gdt->sc_info2 = ctx.info2;

    if (ctx.istatus == GDT_ASYNCINDEX) {
        gdt_async_event(gdt, ctx.service);
        return (ctx.istatus);
    }
    if (ctx.istatus == GDT_SPEZINDEX) {
        GDT_DPRINTF(GDT_D_INVALID, 
                    ("%s: Service unknown or not initialized!\n", 
		     device_get_nameunit(gdt->sc_devnode)));   
        gdt->sc_dvr.size = sizeof(gdt->sc_dvr.eu.driver);
        gdt->sc_dvr.eu.driver.ionode = gdt->sc_hanum;
        gdt_store_event(GDT_ES_DRIVER, 4, &gdt->sc_dvr);
        return (ctx.istatus);
    }

    gccb = &gdt->sc_gccbs[ctx.istatus - 2];
    ctx.service = gccb->gc_service;

    switch (gccb->gc_flags) {
      case GDT_GCF_UNUSED:
        GDT_DPRINTF(GDT_D_INVALID, ("%s: Index (%d) to unused command!\n",
		    device_get_nameunit(gdt->sc_devnode), ctx.istatus));
        gdt->sc_dvr.size = sizeof(gdt->sc_dvr.eu.driver);
        gdt->sc_dvr.eu.driver.ionode = gdt->sc_hanum;
        gdt->sc_dvr.eu.driver.index = ctx.istatus;
        gdt_store_event(GDT_ES_DRIVER, 1, &gdt->sc_dvr);
        gdt_free_ccb(gdt, gccb);
	break;

      case GDT_GCF_INTERNAL:
        break;

      case GDT_GCF_IOCTL:
        ucmd = gccb->gc_ucmd; 
        if (gdt->sc_status == GDT_S_BSY) {
            GDT_DPRINTF(GDT_D_DEBUG, ("iir_intr(%p) ioctl: gccb %p busy\n", 
                                      gdt, gccb));
            TAILQ_INSERT_HEAD(&gdt->sc_ucmd_queue, ucmd, links);
        } else {
            ucmd->status = gdt->sc_status;
            ucmd->info = gdt->sc_info;
            ucmd->complete_flag = TRUE;
            if (ucmd->service == GDT_CACHESERVICE) {
                if (ucmd->OpCode == GDT_IOCTL) {
                    cnt = ucmd->u.ioctl.param_size;
                    if (cnt != 0)
                        bcopy(gccb->gc_scratch, ucmd->data, cnt);
                } else {
                    cnt = ucmd->u.cache.BlockCnt * GDT_SECTOR_SIZE;
                    if (cnt != 0)
                        bcopy(gccb->gc_scratch, ucmd->data, cnt);
                }
            } else {
                cnt = ucmd->u.raw.sdlen;
                if (cnt != 0)
                    bcopy(gccb->gc_scratch, ucmd->data, cnt);
                if (ucmd->u.raw.sense_len != 0) 
                    bcopy(gccb->gc_scratch, ucmd->data, cnt);
            }
            gdt_free_ccb(gdt, gccb);
            /* wakeup */
            wakeup(ucmd);
        }
        gdt_next(gdt); 
        break;

      default:
        gdt_free_ccb(gdt, gccb);
        gdt_sync_event(gdt, ctx.service, ctx.istatus, gccb);
        gdt_next(gdt); 
        break;
    }

    return (ctx.istatus);
}