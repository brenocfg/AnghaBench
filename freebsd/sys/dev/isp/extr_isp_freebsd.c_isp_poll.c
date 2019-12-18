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
struct cam_sim {int dummy; } ;
typedef  int /*<<< orphan*/  ispsoftc_t ;

/* Variables and functions */
 int /*<<< orphan*/  ISP_RUN_ISR (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * cam_sim_softc (struct cam_sim*) ; 

__attribute__((used)) static void
isp_poll(struct cam_sim *sim)
{
	ispsoftc_t *isp = cam_sim_softc(sim);

	ISP_RUN_ISR(isp);
}