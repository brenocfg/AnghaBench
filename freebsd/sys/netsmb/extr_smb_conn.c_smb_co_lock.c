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
struct smb_connobj {int co_flags; int /*<<< orphan*/  co_interlock; int /*<<< orphan*/  co_lock; int /*<<< orphan*/  co_lockcnt; int /*<<< orphan*/ * co_locker; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  MPASS (int) ; 
 int SMBO_GONE ; 
 int /*<<< orphan*/ * curthread ; 
 int /*<<< orphan*/  cv_wait (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * sx_xholder (int /*<<< orphan*/ *) ; 

int
smb_co_lock(struct smb_connobj *cp)
{

	MPASS(sx_xholder(&cp->co_interlock) == curthread); 
	for (;;) {
		if (cp->co_flags & SMBO_GONE)
			return EINVAL;
		if (cp->co_locker == NULL) {
			cp->co_locker = curthread;
			return 0;
		}
		if (cp->co_locker == curthread) {
			cp->co_lockcnt++;
			return 0;
		}
		cv_wait(&cp->co_lock, &cp->co_interlock);
	}
}