#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct ccb_hdr {int target_id; int target_lun; int flags; int /*<<< orphan*/  status; scalar_t__ ccb_sim_ptr; } ;
struct ccb_scsiio {int cdb_len; } ;
union ccb {struct ccb_hdr ccb_h; struct ccb_scsiio csio; } ;
typedef  scalar_t__ u_int8_t ;
struct gdt_softc {int sc_state; scalar_t__ sc_cmd_cnt; scalar_t__ sc_cmd_off; int sc_virt_bus; int /*<<< orphan*/  (* sc_release_event ) (struct gdt_softc*) ;int /*<<< orphan*/  sc_ccb_queue; TYPE_1__* sc_hdr; int /*<<< orphan*/  sc_ucmd_queue; scalar_t__ (* sc_test_busy ) (struct gdt_softc*) ;int /*<<< orphan*/  sc_lock; } ;
struct gdt_ccb {int dummy; } ;
struct cam_sim {int dummy; } ;
typedef  struct ccb_hdr gdt_ucmd_t ;
struct TYPE_6__ {scalar_t__ req_queue_act; scalar_t__ req_queue_max; int /*<<< orphan*/  io_count_act; } ;
struct TYPE_5__ {int /*<<< orphan*/  tqe; } ;
struct TYPE_4__ {int /*<<< orphan*/  hd_present; } ;

/* Variables and functions */
 int CAM_CDB_PHYS ; 
 int /*<<< orphan*/  CAM_DEV_NOT_THERE ; 
 int /*<<< orphan*/  CAM_REQ_INVALID ; 
 int /*<<< orphan*/  DELAY (int) ; 
 int FALSE ; 
 int /*<<< orphan*/  GDT_DPRINTF (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  GDT_D_QUEUE ; 
 int GDT_MAX_HDRIVES ; 
 int GDT_POLLING ; 
 int /*<<< orphan*/  GDT_POLL_TIMEOUT ; 
 int /*<<< orphan*/  MA_OWNED ; 
 scalar_t__ READ_10 ; 
 scalar_t__ READ_6 ; 
 struct ccb_hdr* TAILQ_FIRST (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TAILQ_INSERT_HEAD (int /*<<< orphan*/ *,struct ccb_hdr*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TAILQ_REMOVE (int /*<<< orphan*/ *,struct ccb_hdr*,int /*<<< orphan*/ ) ; 
 int TRUE ; 
 scalar_t__ WRITE_10 ; 
 scalar_t__ WRITE_6 ; 
 int cam_sim_bus (struct cam_sim*) ; 
 struct gdt_ccb* gdt_cache_cmd (struct gdt_softc*,union ccb*) ; 
 int /*<<< orphan*/  gdt_internal_cache_cmd (struct gdt_softc*,union ccb*) ; 
 struct gdt_ccb* gdt_ioctl_cmd (struct gdt_softc*,struct ccb_hdr*) ; 
 struct gdt_ccb* gdt_raw_cmd (struct gdt_softc*,union ccb*) ; 
 TYPE_3__ gdt_stat ; 
 int /*<<< orphan*/  gdt_wait (struct gdt_softc*,struct gdt_ccb*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  links ; 
 int /*<<< orphan*/  mtx_assert (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__* scsiio_cdb_ptr (struct ccb_scsiio*) ; 
 TYPE_2__ sim_links ; 
 scalar_t__ stub1 (struct gdt_softc*) ; 
 scalar_t__ stub2 (struct gdt_softc*) ; 
 int /*<<< orphan*/  stub3 (struct gdt_softc*) ; 
 int /*<<< orphan*/  xpt_done (union ccb*) ; 

void    
gdt_next(struct gdt_softc *gdt)
{
    union ccb *ccb;
    gdt_ucmd_t *ucmd;
    struct cam_sim *sim;
    int bus, target, lun;
    int next_cmd;

    struct ccb_scsiio *csio;
    struct ccb_hdr *ccbh;
    struct gdt_ccb *gccb = NULL;
    u_int8_t cmd;

    GDT_DPRINTF(GDT_D_QUEUE, ("gdt_next(%p)\n", gdt));

    mtx_assert(&gdt->sc_lock, MA_OWNED);
    if (gdt->sc_test_busy(gdt)) {
        if (!(gdt->sc_state & GDT_POLLING)) {
            return;
        }
        while (gdt->sc_test_busy(gdt))
            DELAY(1);
    }

    gdt->sc_cmd_cnt = gdt->sc_cmd_off = 0;
    next_cmd = TRUE;
    for (;;) {
        /* I/Os in queue? controller ready? */
        if (!TAILQ_FIRST(&gdt->sc_ucmd_queue) &&
            !TAILQ_FIRST(&gdt->sc_ccb_queue))
            break;

        /* 1.: I/Os without ccb (IOCTLs) */
        ucmd = TAILQ_FIRST(&gdt->sc_ucmd_queue);
        if (ucmd != NULL) {
            TAILQ_REMOVE(&gdt->sc_ucmd_queue, ucmd, links);
            if ((gccb = gdt_ioctl_cmd(gdt, ucmd)) == NULL) {
                TAILQ_INSERT_HEAD(&gdt->sc_ucmd_queue, ucmd, links);
                break;
            }
            break;      
            /* wenn mehrere Kdos. zulassen: if (!gdt_polling) continue; */
        }

        /* 2.: I/Os with ccb */
        ccb = (union ccb *)TAILQ_FIRST(&gdt->sc_ccb_queue); 
        /* ist dann immer != NULL, da oben getestet */
        sim = (struct cam_sim *)ccb->ccb_h.ccb_sim_ptr;
        bus = cam_sim_bus(sim);
        target = ccb->ccb_h.target_id;
        lun = ccb->ccb_h.target_lun;
    
        TAILQ_REMOVE(&gdt->sc_ccb_queue, &ccb->ccb_h, sim_links.tqe);
        --gdt_stat.req_queue_act;
        /* ccb->ccb_h.func_code is XPT_SCSI_IO */
        GDT_DPRINTF(GDT_D_QUEUE, ("XPT_SCSI_IO flags 0x%x)\n", 
                                  ccb->ccb_h.flags));
        csio = &ccb->csio;
        ccbh = &ccb->ccb_h;
        cmd  = scsiio_cdb_ptr(csio)[0];
        /* Max CDB length is 12 bytes, can't be phys addr */
        if (csio->cdb_len > 12 || (ccbh->flags & CAM_CDB_PHYS)) { 
            ccbh->status = CAM_REQ_INVALID;
            --gdt_stat.io_count_act;
            xpt_done(ccb);
        } else if (bus != gdt->sc_virt_bus) {
            /* raw service command */
            if ((gccb = gdt_raw_cmd(gdt, ccb)) == NULL) {
                TAILQ_INSERT_HEAD(&gdt->sc_ccb_queue, &ccb->ccb_h, 
                                  sim_links.tqe);
                ++gdt_stat.req_queue_act;
                if (gdt_stat.req_queue_act > gdt_stat.req_queue_max)
                    gdt_stat.req_queue_max = gdt_stat.req_queue_act;
                next_cmd = FALSE;
            }
        } else if (target >= GDT_MAX_HDRIVES || 
                   !gdt->sc_hdr[target].hd_present || lun != 0) {
            ccbh->status = CAM_DEV_NOT_THERE;
            --gdt_stat.io_count_act;
            xpt_done(ccb);
        } else {
            /* cache service command */
            if (cmd == READ_6  || cmd == WRITE_6 ||
                cmd == READ_10 || cmd == WRITE_10) {
                if ((gccb = gdt_cache_cmd(gdt, ccb)) == NULL) {
                    TAILQ_INSERT_HEAD(&gdt->sc_ccb_queue, &ccb->ccb_h, 
                                      sim_links.tqe);
                    ++gdt_stat.req_queue_act;
                    if (gdt_stat.req_queue_act > gdt_stat.req_queue_max)
                        gdt_stat.req_queue_max = gdt_stat.req_queue_act;
                    next_cmd = FALSE;
                }
            } else {
                gdt_internal_cache_cmd(gdt, ccb);
            }
        }           
        if ((gdt->sc_state & GDT_POLLING) || !next_cmd)
            break;
    }
    if (gdt->sc_cmd_cnt > 0)
        gdt->sc_release_event(gdt);

    if ((gdt->sc_state & GDT_POLLING) && gdt->sc_cmd_cnt > 0) {
        gdt_wait(gdt, gccb, GDT_POLL_TIMEOUT);
    }
}