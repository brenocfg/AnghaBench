#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_4__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int flags; int timeout; int /*<<< orphan*/  status; scalar_t__ ccb_sim_ptr; } ;
union ccb {TYPE_1__ ccb_h; } ;
typedef  int /*<<< orphan*/  u_int32_t ;
struct gdt_softc {int /*<<< orphan*/  (* sc_copy_cmd ) (struct gdt_softc*,struct gdt_ccb*) ;int /*<<< orphan*/  sc_buffer_dmat; int /*<<< orphan*/  sc_lock; } ;
struct gdt_ccb {scalar_t__ gc_service; int /*<<< orphan*/  gc_timeout; int /*<<< orphan*/  gc_dmamap; void* gc_cmd_len; scalar_t__ gc_cmd; union ccb* gc_ccb; } ;
struct cam_sim {int dummy; } ;
typedef  int /*<<< orphan*/  caddr_t ;
struct TYPE_6__ {int ds_addr; int ds_len; } ;
typedef  TYPE_2__ bus_dma_segment_t ;
struct TYPE_7__ {int sg_count_act; int sg_count_max; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUS_DMASYNC_PREREAD ; 
 int /*<<< orphan*/  BUS_DMASYNC_PREWRITE ; 
 int CAM_DIR_IN ; 
 int CAM_DIR_MASK ; 
 int /*<<< orphan*/  CAM_SIM_QUEUED ; 
 scalar_t__ GDT_CACHESERVICE ; 
 scalar_t__ GDT_CACHE_DESTADDR ; 
 scalar_t__ GDT_CACHE_SG_CANZ ; 
 scalar_t__ GDT_CACHE_SG_LST ; 
 scalar_t__ GDT_CMD_UNION ; 
 int /*<<< orphan*/  GDT_DPRINTF (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  GDT_D_CMD ; 
 scalar_t__ GDT_RAW_SDATA ; 
 scalar_t__ GDT_RAW_SG_LST ; 
 scalar_t__ GDT_RAW_SG_RANZ ; 
 scalar_t__ GDT_SG_LEN ; 
 scalar_t__ GDT_SG_PTR ; 
 int GDT_SG_SZ ; 
 int /*<<< orphan*/  MA_OWNED ; 
 int SBT_1MS ; 
 int /*<<< orphan*/  bus_dmamap_sync (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  callout_reset_sbt (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct gdt_softc* cam_sim_softc (struct cam_sim*) ; 
 int /*<<< orphan*/  gdt_enc32 (scalar_t__,int) ; 
 TYPE_4__ gdt_stat ; 
 int /*<<< orphan*/  iir_timeout ; 
 int /*<<< orphan*/  mtx_assert (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 void* roundup (scalar_t__,int) ; 
 int /*<<< orphan*/  stub1 (struct gdt_softc*,struct gdt_ccb*) ; 

__attribute__((used)) static void     
gdtexecuteccb(void *arg, bus_dma_segment_t *dm_segs, int nseg, int error)
{
    struct gdt_ccb *gccb;
    union ccb *ccb;
    struct gdt_softc *gdt;
    int i;

    gccb = (struct gdt_ccb *)arg;
    ccb = gccb->gc_ccb;
    gdt = cam_sim_softc((struct cam_sim *)ccb->ccb_h.ccb_sim_ptr);
    mtx_assert(&gdt->sc_lock, MA_OWNED);

    GDT_DPRINTF(GDT_D_CMD, ("gdtexecuteccb(%p, %p, %p, %d, %d)\n", 
                            gdt, gccb, dm_segs, nseg, error));
    gdt_stat.sg_count_act = nseg;
    if (nseg > gdt_stat.sg_count_max)
        gdt_stat.sg_count_max = nseg;

    /* Copy the segments into our SG list */
    if (gccb->gc_service == GDT_CACHESERVICE) {
        for (i = 0; i < nseg; ++i) {
            gdt_enc32(gccb->gc_cmd + GDT_CMD_UNION + GDT_CACHE_SG_LST +
                      i * GDT_SG_SZ + GDT_SG_PTR, dm_segs->ds_addr);
            gdt_enc32(gccb->gc_cmd + GDT_CMD_UNION + GDT_CACHE_SG_LST +
                      i * GDT_SG_SZ + GDT_SG_LEN, dm_segs->ds_len);
            dm_segs++;
        }
        gdt_enc32(gccb->gc_cmd + GDT_CMD_UNION + GDT_CACHE_SG_CANZ,      
                  nseg);
        gdt_enc32(gccb->gc_cmd + GDT_CMD_UNION + GDT_CACHE_DESTADDR, 
                  0xffffffffUL);

        gccb->gc_cmd_len = roundup(GDT_CMD_UNION + GDT_CACHE_SG_LST +
                                  nseg * GDT_SG_SZ, sizeof(u_int32_t));
    } else {
        for (i = 0; i < nseg; ++i) {
            gdt_enc32(gccb->gc_cmd + GDT_CMD_UNION + GDT_RAW_SG_LST +
                      i * GDT_SG_SZ + GDT_SG_PTR, dm_segs->ds_addr);
            gdt_enc32(gccb->gc_cmd + GDT_CMD_UNION + GDT_RAW_SG_LST +
                      i * GDT_SG_SZ + GDT_SG_LEN, dm_segs->ds_len);
            dm_segs++;
        }
        gdt_enc32(gccb->gc_cmd + GDT_CMD_UNION + GDT_RAW_SG_RANZ,        
                  nseg);
        gdt_enc32(gccb->gc_cmd + GDT_CMD_UNION + GDT_RAW_SDATA, 
                  0xffffffffUL);

        gccb->gc_cmd_len = roundup(GDT_CMD_UNION + GDT_RAW_SG_LST +
                                  nseg * GDT_SG_SZ, sizeof(u_int32_t));
    }

    if (nseg != 0) {
        bus_dmamap_sync(gdt->sc_buffer_dmat, gccb->gc_dmamap, 
            (ccb->ccb_h.flags & CAM_DIR_MASK) == CAM_DIR_IN ?
            BUS_DMASYNC_PREREAD : BUS_DMASYNC_PREWRITE);
    }
    
    /* We must NOT abort the command here if CAM_REQ_INPROG is not set,
     * because command semaphore is already set!
     */
    
    ccb->ccb_h.status |= CAM_SIM_QUEUED;
    /* timeout handling */
    callout_reset_sbt(&gccb->gc_timeout, SBT_1MS * ccb->ccb_h.timeout, 0,
      iir_timeout, (caddr_t)gccb, 0);

    gdt->sc_copy_cmd(gdt, gccb);
}