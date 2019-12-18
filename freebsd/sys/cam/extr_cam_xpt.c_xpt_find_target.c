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
typedef  scalar_t__ target_id_t ;
struct cam_et {scalar_t__ target_id; int /*<<< orphan*/  refcount; } ;
struct cam_eb {int /*<<< orphan*/  et_entries; int /*<<< orphan*/  eb_mtx; } ;

/* Variables and functions */
 int /*<<< orphan*/  MA_OWNED ; 
 struct cam_et* TAILQ_FIRST (int /*<<< orphan*/ *) ; 
 struct cam_et* TAILQ_NEXT (struct cam_et*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  links ; 
 int /*<<< orphan*/  mtx_assert (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct cam_et *
xpt_find_target(struct cam_eb *bus, target_id_t	target_id)
{
	struct cam_et *target;

	mtx_assert(&bus->eb_mtx, MA_OWNED);
	for (target = TAILQ_FIRST(&bus->et_entries);
	     target != NULL;
	     target = TAILQ_NEXT(target, links)) {
		if (target->target_id == target_id) {
			target->refcount++;
			break;
		}
	}
	return (target);
}