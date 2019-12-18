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
struct gdt_softc {int /*<<< orphan*/  sc_lock; int /*<<< orphan*/  sc_ucmd_queue; TYPE_1__* sc_hdr; int /*<<< orphan*/  sc_pending_gccb; int /*<<< orphan*/  sc_state; int /*<<< orphan*/  sc_devnode; } ;
struct TYPE_5__ {int DeviceNo; } ;
struct TYPE_6__ {TYPE_2__ cache; } ;
struct gdt_ccb {int /*<<< orphan*/  complete_flag; TYPE_3__ u; int /*<<< orphan*/  OpCode; int /*<<< orphan*/  service; } ;
typedef  struct gdt_ccb gdt_ucmd_t ;
struct TYPE_4__ {scalar_t__ hd_present; } ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  GDT_CACHESERVICE ; 
 int /*<<< orphan*/  GDT_DPRINTF (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  GDT_D_CMD ; 
 int /*<<< orphan*/  GDT_FLUSH ; 
 int GDT_MAX_HDRIVES ; 
 int /*<<< orphan*/  GDT_SHUTDOWN ; 
 int /*<<< orphan*/  M_DEVBUF ; 
 int /*<<< orphan*/  M_GDTBUF ; 
 int /*<<< orphan*/  M_NOWAIT ; 
 int PCATCH ; 
 int PRIBIO ; 
 struct gdt_ccb* SLIST_FIRST (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TAILQ_INSERT_TAIL (int /*<<< orphan*/ *,struct gdt_ccb*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bzero (struct gdt_ccb*,int) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  free (struct gdt_ccb*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gdt_next (struct gdt_softc*) ; 
 int hz ; 
 int /*<<< orphan*/  links ; 
 struct gdt_ccb* malloc (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_sleep (struct gdt_ccb*,int /*<<< orphan*/ *,int,char*,int) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  printf (char*) ; 

__attribute__((used)) static void     
iir_shutdown( void *arg, int howto )
{
    struct gdt_softc *gdt;
    struct gdt_ccb *gccb;
    gdt_ucmd_t *ucmd;
    int i;

    gdt = (struct gdt_softc *)arg;
    GDT_DPRINTF(GDT_D_CMD, ("iir_shutdown(%p, %d)\n", gdt, howto));

    device_printf(gdt->sc_devnode,
	"Flushing all Host Drives. Please wait ...  ");

    /* allocate ucmd buffer */
    ucmd = malloc(sizeof(gdt_ucmd_t), M_GDTBUF, M_NOWAIT);
    if (ucmd == NULL) {
	printf("\n");
        device_printf(gdt->sc_devnode,
	    "iir_shutdown(): Cannot allocate resource\n");
        return;
    }
    bzero(ucmd, sizeof(gdt_ucmd_t));

    /* wait for pending IOs */
    mtx_lock(&gdt->sc_lock);
    gdt->sc_state = GDT_SHUTDOWN;
    if ((gccb = SLIST_FIRST(&gdt->sc_pending_gccb)) != NULL)
        mtx_sleep(gccb, &gdt->sc_lock, PCATCH | PRIBIO, "iirshw", 100 * hz);

    /* flush */
    for (i = 0; i < GDT_MAX_HDRIVES; ++i) {
        if (gdt->sc_hdr[i].hd_present) {
            ucmd->service = GDT_CACHESERVICE;
            ucmd->OpCode = GDT_FLUSH;
            ucmd->u.cache.DeviceNo = i;
            TAILQ_INSERT_TAIL(&gdt->sc_ucmd_queue, ucmd, links);
            ucmd->complete_flag = FALSE;
            gdt_next(gdt);
            if (!ucmd->complete_flag)
                mtx_sleep(ucmd, &gdt->sc_lock, PCATCH | PRIBIO, "iirshw",
		    10 * hz);
        }
    }
    mtx_unlock(&gdt->sc_lock);

    free(ucmd, M_DEVBUF);
    printf("Done.\n");
}