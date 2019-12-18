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
struct tty {int t_revokecnt; int /*<<< orphan*/  t_mtx; } ;
struct cv {int dummy; } ;

/* Variables and functions */
 int ENXIO ; 
 int ERESTART ; 
 int MA_NOTRECURSED ; 
 int MA_OWNED ; 
 int /*<<< orphan*/  MPASS (int) ; 
 int cv_timedwait_sig (struct cv*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ tty_gone (struct tty*) ; 
 int /*<<< orphan*/  tty_lock_assert (struct tty*,int) ; 

int
tty_timedwait(struct tty *tp, struct cv *cv, int hz)
{
	int error;
	int revokecnt = tp->t_revokecnt;

	tty_lock_assert(tp, MA_OWNED|MA_NOTRECURSED);
	MPASS(!tty_gone(tp));

	error = cv_timedwait_sig(cv, tp->t_mtx, hz);

	/* Bail out when the device slipped away. */
	if (tty_gone(tp))
		return (ENXIO);

	/* Restart the system call when we may have been revoked. */
	if (tp->t_revokecnt != revokecnt)
		return (ERESTART);

	return (error);
}