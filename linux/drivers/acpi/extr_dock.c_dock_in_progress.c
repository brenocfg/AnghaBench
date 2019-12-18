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
struct dock_station {int flags; scalar_t__ last_dock_time; } ;

/* Variables and functions */
 int DOCK_DOCKING ; 
 scalar_t__ HZ ; 
 int /*<<< orphan*/  jiffies ; 
 scalar_t__ time_before (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static int dock_in_progress(struct dock_station *ds)
{
	if ((ds->flags & DOCK_DOCKING) ||
	    time_before(jiffies, (ds->last_dock_time + HZ)))
		return 1;
	return 0;
}