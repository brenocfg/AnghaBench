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
typedef  int /*<<< orphan*/  IAL_ADAPTER_T ;

/* Variables and functions */
 int /*<<< orphan*/ * cam_sim_softc (struct cam_sim*) ; 
 int /*<<< orphan*/  hpt_intr_locked (void*) ; 

__attribute__((used)) static void
hpt_poll(struct cam_sim *sim)
{
	IAL_ADAPTER_T *pAdapter;

	pAdapter = cam_sim_softc(sim);
	
	hpt_intr_locked((void *)cam_sim_softc(sim));
}