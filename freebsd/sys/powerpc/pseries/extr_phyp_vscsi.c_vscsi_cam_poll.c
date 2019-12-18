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
struct vscsi_softc {int dummy; } ;
struct cam_sim {int dummy; } ;

/* Variables and functions */
 struct vscsi_softc* cam_sim_softc (struct cam_sim*) ; 
 int /*<<< orphan*/  vscsi_check_response_queue (struct vscsi_softc*) ; 

__attribute__((used)) static void
vscsi_cam_poll(struct cam_sim *sim)
{
	struct vscsi_softc *sc = cam_sim_softc(sim);

	vscsi_check_response_queue(sc);
}