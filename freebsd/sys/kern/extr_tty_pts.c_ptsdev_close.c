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
struct tty {int dummy; } ;
struct thread {int dummy; } ;
struct file {int /*<<< orphan*/ * f_vnode; struct tty* f_data; } ;
struct TYPE_2__ {int (* fo_close ) (struct file*,struct thread*) ;} ;

/* Variables and functions */
 int stub1 (struct file*,struct thread*) ; 
 int /*<<< orphan*/  tty_lock (struct tty*) ; 
 int /*<<< orphan*/  tty_rel_gone (struct tty*) ; 
 TYPE_1__ vnops ; 

__attribute__((used)) static int
ptsdev_close(struct file *fp, struct thread *td)
{
	struct tty *tp = fp->f_data;

	/* Deallocate TTY device. */
	tty_lock(tp);
	tty_rel_gone(tp);

	/*
	 * Open of /dev/ptmx or /dev/ptyXX changes the type of file
	 * from DTYPE_VNODE to DTYPE_PTS. vn_open() increases vnode
	 * use count, we need to decrement it, and possibly do other
	 * required cleanup.
	 */
	if (fp->f_vnode != NULL)
		return (vnops.fo_close(fp, td));

	return (0);
}