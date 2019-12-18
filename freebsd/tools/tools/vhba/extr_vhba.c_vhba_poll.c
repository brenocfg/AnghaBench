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
typedef  int /*<<< orphan*/  vhba_softc_t ;
struct cam_sim {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/ * cam_sim_softc (struct cam_sim*) ; 
 int /*<<< orphan*/  vhba_kick (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
vhba_poll(struct cam_sim *sim)
{
	vhba_softc_t *vhba = cam_sim_softc(sim);
	vhba_kick(vhba);
}