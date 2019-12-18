#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct lock_object {TYPE_1__* lo_witness; int /*<<< orphan*/  lo_name; } ;
struct lock_instance {int li_flags; int /*<<< orphan*/  li_line; int /*<<< orphan*/  li_file; struct lock_object* li_lock; } ;
struct TYPE_4__ {int /*<<< orphan*/  lc_name; } ;
struct TYPE_3__ {int /*<<< orphan*/  w_name; } ;

/* Variables and functions */
 int LI_EXCLUSIVE ; 
 int LI_RECURSEMASK ; 
 TYPE_2__* LOCK_CLASS (struct lock_object*) ; 
 int /*<<< orphan*/  fixup_filename (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
witness_list_lock(struct lock_instance *instance,
    int (*prnt)(const char *fmt, ...))
{
	struct lock_object *lock;

	lock = instance->li_lock;
	prnt("%s %s %s", (instance->li_flags & LI_EXCLUSIVE) != 0 ?
	    "exclusive" : "shared", LOCK_CLASS(lock)->lc_name, lock->lo_name);
	if (lock->lo_witness->w_name != lock->lo_name)
		prnt(" (%s)", lock->lo_witness->w_name);
	prnt(" r = %d (%p) locked @ %s:%d\n",
	    instance->li_flags & LI_RECURSEMASK, lock,
	    fixup_filename(instance->li_file), instance->li_line);
}