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
typedef  int u_int ;
struct lock_object {int dummy; } ;
struct lock_class {int /*<<< orphan*/  (* lc_unlock ) (struct lock_object*) ;} ;

/* Variables and functions */
 int LK_INTERLOCK ; 
 struct lock_class* LOCK_CLASS (struct lock_object*) ; 
 scalar_t__ __predict_false (int) ; 
 int /*<<< orphan*/  kick_proc0 () ; 
 int /*<<< orphan*/  stub1 (struct lock_object*) ; 

__attribute__((used)) static void
lockmgr_exit(u_int flags, struct lock_object *ilk, int wakeup_swapper)
{
	struct lock_class *class;

	if (flags & LK_INTERLOCK) {
		class = LOCK_CLASS(ilk);
		class->lc_unlock(ilk);
	}

	if (__predict_false(wakeup_swapper))
		kick_proc0();
}