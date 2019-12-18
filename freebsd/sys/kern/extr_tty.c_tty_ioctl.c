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
typedef  int /*<<< orphan*/  u_long ;
struct tty {int dummy; } ;
struct thread {int dummy; } ;

/* Variables and functions */
 int ENOIOCTL ; 
 int ENXIO ; 
 int /*<<< orphan*/  MA_OWNED ; 
 int tty_generic_ioctl (struct tty*,int /*<<< orphan*/ ,void*,int,struct thread*) ; 
 scalar_t__ tty_gone (struct tty*) ; 
 int /*<<< orphan*/  tty_lock_assert (struct tty*,int /*<<< orphan*/ ) ; 
 int ttydevsw_ioctl (struct tty*,int /*<<< orphan*/ ,void*,struct thread*) ; 

int
tty_ioctl(struct tty *tp, u_long cmd, void *data, int fflag, struct thread *td)
{
	int error;

	tty_lock_assert(tp, MA_OWNED);

	if (tty_gone(tp))
		return (ENXIO);

	error = ttydevsw_ioctl(tp, cmd, data, td);
	if (error == ENOIOCTL)
		error = tty_generic_ioctl(tp, cmd, data, fflag, td);

	return (error);
}