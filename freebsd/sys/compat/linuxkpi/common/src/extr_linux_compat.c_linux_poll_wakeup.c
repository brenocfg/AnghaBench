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
struct TYPE_2__ {int /*<<< orphan*/  si_note; } ;
struct linux_file {int f_kqflags; int /*<<< orphan*/  f_kqlock; TYPE_1__ f_selinfo; } ;

/* Variables and functions */
 int /*<<< orphan*/  KNOTE_LOCKED (int /*<<< orphan*/ *,int) ; 
 int LINUX_KQ_FLAG_NEED_READ ; 
 int LINUX_KQ_FLAG_NEED_WRITE ; 
 int /*<<< orphan*/  selwakeup (TYPE_1__*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

void
linux_poll_wakeup(struct linux_file *filp)
{
	/* this function should be NULL-safe */
	if (filp == NULL)
		return;

	selwakeup(&filp->f_selinfo);

	spin_lock(&filp->f_kqlock);
	filp->f_kqflags |= LINUX_KQ_FLAG_NEED_READ |
	    LINUX_KQ_FLAG_NEED_WRITE;

	/* make sure the "knote" gets woken up */
	KNOTE_LOCKED(&filp->f_selinfo.si_note, 1);
	spin_unlock(&filp->f_kqlock);
}