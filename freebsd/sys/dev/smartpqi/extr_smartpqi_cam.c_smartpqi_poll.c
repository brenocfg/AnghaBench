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
struct pqisrc_softstate {int intr_count; } ;
struct cam_sim {int dummy; } ;

/* Variables and functions */
 struct pqisrc_softstate* cam_sim_softc (struct cam_sim*) ; 
 int /*<<< orphan*/  pqisrc_process_response_queue (struct pqisrc_softstate*,int) ; 

__attribute__((used)) static void smartpqi_poll(struct cam_sim *sim)
{
	struct pqisrc_softstate *softs = cam_sim_softc(sim);
	int i;

	for (i = 1; i < softs->intr_count; i++ )
		pqisrc_process_response_queue(softs, i);
}