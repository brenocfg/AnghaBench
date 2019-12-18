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
typedef  int /*<<< orphan*/  sigset_t ;
struct TYPE_2__ {int /*<<< orphan*/  lock; } ;
typedef  TYPE_1__ Lock ;

/* Variables and functions */
 int /*<<< orphan*/  SIG_BLOCK ; 
 int /*<<< orphan*/  SIG_SETMASK ; 
 int /*<<< orphan*/  WAFLAG ; 
 scalar_t__ atomic_cmpset_acq_int (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ atomic_fetchadd_int (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  fullsigmask ; 
 int /*<<< orphan*/  oldsigmask ; 
 int /*<<< orphan*/  sigprocmask (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wnested ; 

__attribute__((used)) static void
def_wlock_acquire(void *lock)
{
	Lock *l;
	sigset_t tmp_oldsigmask;

	l = (Lock *)lock;
	for (;;) {
		sigprocmask(SIG_BLOCK, &fullsigmask, &tmp_oldsigmask);
		if (atomic_cmpset_acq_int(&l->lock, 0, WAFLAG))
			break;
		sigprocmask(SIG_SETMASK, &tmp_oldsigmask, NULL);
	}
	if (atomic_fetchadd_int(&wnested, 1) == 0)
		oldsigmask = tmp_oldsigmask;
}