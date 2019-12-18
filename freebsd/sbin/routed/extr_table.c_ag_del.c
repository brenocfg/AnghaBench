#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct ag_info {struct ag_info* ag_fine; TYPE_1__* ag_cors; } ;
struct TYPE_2__ {struct ag_info* ag_fine; } ;

/* Variables and functions */
 int /*<<< orphan*/  CHECK_AG () ; 
 struct ag_info* ag_avail ; 
 struct ag_info* ag_corsest ; 
 TYPE_1__* ag_finest ; 

__attribute__((used)) static void
ag_del(struct ag_info *ag)
{
	CHECK_AG();

	if (ag->ag_cors == NULL)
		ag_corsest = ag->ag_fine;
	else
		ag->ag_cors->ag_fine = ag->ag_fine;

	if (ag->ag_fine == NULL)
		ag_finest = ag->ag_cors;
	else
		ag->ag_fine->ag_cors = ag->ag_cors;

	ag->ag_fine = ag_avail;
	ag_avail = ag;

	CHECK_AG();
}