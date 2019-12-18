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
struct local_zones {int /*<<< orphan*/  ztree; int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  free (struct local_zones*) ; 
 int /*<<< orphan*/  lock_rw_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lzdel ; 
 int /*<<< orphan*/  traverse_postorder (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void 
local_zones_delete(struct local_zones* zones)
{
	if(!zones)
		return;
	lock_rw_destroy(&zones->lock);
	/* walk through zones and delete them all */
	traverse_postorder(&zones->ztree, lzdel, NULL);
	free(zones);
}