#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;
struct TYPE_4__ {int /*<<< orphan*/  nvidia_head; TYPE_1__ drm_crtc; } ;
struct dc_softc {TYPE_2__ tegra_crtc; } ;

/* Variables and functions */
 int /*<<< orphan*/  DC_CMD_INT_STATUS ; 
 int RD4 (struct dc_softc*,int /*<<< orphan*/ ) ; 
 int VBLANK_INT ; 
 int /*<<< orphan*/  WR4 (struct dc_softc*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  dc_finish_page_flip (struct dc_softc*) ; 
 int /*<<< orphan*/  drm_handle_vblank (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
dc_intr(void *arg)
{
	struct dc_softc *sc;
	uint32_t status;

	sc = arg;

	/* Confirm interrupt */
	status = RD4(sc, DC_CMD_INT_STATUS);
	WR4(sc, DC_CMD_INT_STATUS, status);
	if (status & VBLANK_INT) {
		drm_handle_vblank(sc->tegra_crtc.drm_crtc.dev,
		    sc->tegra_crtc.nvidia_head);
		dc_finish_page_flip(sc);
	}
}