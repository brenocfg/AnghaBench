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
struct cam_eb {scalar_t__ path_id; int /*<<< orphan*/  refcount; } ;
typedef  scalar_t__ path_id_t ;
struct TYPE_2__ {int /*<<< orphan*/  xpt_busses; } ;

/* Variables and functions */
 struct cam_eb* TAILQ_FIRST (int /*<<< orphan*/ *) ; 
 struct cam_eb* TAILQ_NEXT (struct cam_eb*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  links ; 
 int /*<<< orphan*/  xpt_lock_buses () ; 
 int /*<<< orphan*/  xpt_unlock_buses () ; 
 TYPE_1__ xsoftc ; 

__attribute__((used)) static struct cam_eb *
xpt_find_bus(path_id_t path_id)
{
	struct cam_eb *bus;

	xpt_lock_buses();
	for (bus = TAILQ_FIRST(&xsoftc.xpt_busses);
	     bus != NULL;
	     bus = TAILQ_NEXT(bus, links)) {
		if (bus->path_id == path_id) {
			bus->refcount++;
			break;
		}
	}
	xpt_unlock_buses();
	return (bus);
}