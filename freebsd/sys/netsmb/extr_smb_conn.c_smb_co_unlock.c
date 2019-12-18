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
struct smb_connobj {scalar_t__ co_locker; scalar_t__ co_lockcnt; int /*<<< orphan*/  co_lock; int /*<<< orphan*/  co_interlock; } ;

/* Variables and functions */
 int /*<<< orphan*/  MPASS (int) ; 
 scalar_t__ curthread ; 
 int /*<<< orphan*/  cv_signal (int /*<<< orphan*/ *) ; 
 scalar_t__ sx_xholder (int /*<<< orphan*/ *) ; 

void
smb_co_unlock(struct smb_connobj *cp)
{

	MPASS(sx_xholder(&cp->co_interlock) == curthread); 
	MPASS(cp->co_locker == curthread);
	if (cp->co_lockcnt != 0) {
		cp->co_lockcnt--;
		return;
	}
	cp->co_locker = NULL;
	cv_signal(&cp->co_lock);
}