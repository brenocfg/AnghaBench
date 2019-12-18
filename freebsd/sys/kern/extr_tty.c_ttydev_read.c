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
struct uio {int dummy; } ;
struct tty {int dummy; } ;
struct cdev {struct tty* si_drv1; } ;

/* Variables and functions */
 int ENXIO ; 
 int /*<<< orphan*/  tty_unlock (struct tty*) ; 
 int ttydev_enter (struct tty*) ; 
 int ttydisc_read (struct tty*,struct uio*,int) ; 

__attribute__((used)) static int
ttydev_read(struct cdev *dev, struct uio *uio, int ioflag)
{
	struct tty *tp = dev->si_drv1;
	int error;

	error = ttydev_enter(tp);
	if (error)
		goto done;
	error = ttydisc_read(tp, uio, ioflag);
	tty_unlock(tp);

	/*
	 * The read() call should not throw an error when the device is
	 * being destroyed. Silently convert it to an EOF.
	 */
done:	if (error == ENXIO)
		error = 0;
	return (error);
}