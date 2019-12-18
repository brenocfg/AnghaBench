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
struct view {struct view* name; int /*<<< orphan*/  respip_set; int /*<<< orphan*/  local_zones; int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  free (struct view*) ; 
 int /*<<< orphan*/  local_zones_delete (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lock_rw_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  respip_set_delete (int /*<<< orphan*/ ) ; 

void 
view_delete(struct view* v)
{
	if(!v)
		return;
	lock_rw_destroy(&v->lock);
	local_zones_delete(v->local_zones);
	respip_set_delete(v->respip_set);
	free(v->name);
	free(v);
}