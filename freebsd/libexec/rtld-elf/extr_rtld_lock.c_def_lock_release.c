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
struct TYPE_2__ {int lock; } ;
typedef  TYPE_1__ Lock ;

/* Variables and functions */
 int RC_INCR ; 
 int /*<<< orphan*/  SIG_SETMASK ; 
 int WAFLAG ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  atomic_add_rel_int (int*,int) ; 
 int atomic_fetchadd_int (scalar_t__*,int) ; 
 int /*<<< orphan*/  oldsigmask ; 
 int /*<<< orphan*/  sigprocmask (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ wnested ; 

__attribute__((used)) static void
def_lock_release(void *lock)
{
	Lock *l;

	l = (Lock *)lock;
	if ((l->lock & WAFLAG) == 0)
		atomic_add_rel_int(&l->lock, -RC_INCR);
	else {
		assert(wnested > 0);
		atomic_add_rel_int(&l->lock, -WAFLAG);
		if (atomic_fetchadd_int(&wnested, -1) == 1)
			sigprocmask(SIG_SETMASK, &oldsigmask, NULL);
	}
}