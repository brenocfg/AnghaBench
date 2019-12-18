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
struct cd_softc {int flags; int /*<<< orphan*/  disk; int /*<<< orphan*/  mediapoll_c; int /*<<< orphan*/  sysctl_ctx; } ;
struct cam_periph {int /*<<< orphan*/  path; scalar_t__ softc; } ;

/* Variables and functions */
 int CD_FLAG_SCTX_INIT ; 
 int /*<<< orphan*/  M_DEVBUF ; 
 int /*<<< orphan*/  callout_drain (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cam_periph_lock (struct cam_periph*) ; 
 int /*<<< orphan*/  cam_periph_unlock (struct cam_periph*) ; 
 int /*<<< orphan*/  disk_destroy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (struct cd_softc*,int /*<<< orphan*/ ) ; 
 scalar_t__ sysctl_ctx_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xpt_print (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void
cdcleanup(struct cam_periph *periph)
{
	struct cd_softc *softc;

	softc = (struct cd_softc *)periph->softc;

	cam_periph_unlock(periph);
	if ((softc->flags & CD_FLAG_SCTX_INIT) != 0
	    && sysctl_ctx_free(&softc->sysctl_ctx) != 0) {
		xpt_print(periph->path, "can't remove sysctl context\n");
	}

	callout_drain(&softc->mediapoll_c);
	disk_destroy(softc->disk);
	free(softc, M_DEVBUF);
	cam_periph_lock(periph);
}