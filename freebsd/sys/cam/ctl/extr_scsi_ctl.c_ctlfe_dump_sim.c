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
struct cam_sim {char* sim_name; int unit_number; int max_dev_openings; int /*<<< orphan*/  max_tagged_dev_openings; } ;

/* Variables and functions */
 int /*<<< orphan*/  printf (char*,char*,int,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
ctlfe_dump_sim(struct cam_sim *sim)
{

	printf("%s%d: max dev openings: %d, max tagged dev openings: %d\n",
	    sim->sim_name, sim->unit_number, sim->max_dev_openings,
	    sim->max_tagged_dev_openings);
}