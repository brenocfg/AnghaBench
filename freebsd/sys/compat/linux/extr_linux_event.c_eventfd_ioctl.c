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
typedef  int u_long ;
struct ucred {int dummy; } ;
struct thread {int dummy; } ;
struct file {scalar_t__ f_type; int /*<<< orphan*/  f_flag; int /*<<< orphan*/ * f_data; } ;

/* Variables and functions */
 scalar_t__ DTYPE_LINUXEFD ; 
 scalar_t__ DTYPE_LINUXTFD ; 
 int EINVAL ; 
 int ENXIO ; 
#define  FIOASYNC 129 
#define  FIONBIO 128 
 int /*<<< orphan*/  FNONBLOCK ; 
 int /*<<< orphan*/  atomic_clear_int (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  atomic_set_int (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
eventfd_ioctl(struct file *fp, u_long cmd, void *data,
    struct ucred *active_cred, struct thread *td)
{

	if (fp->f_data == NULL || (fp->f_type != DTYPE_LINUXEFD &&
	    fp->f_type != DTYPE_LINUXTFD))
		return (EINVAL);

	switch (cmd)
	{
	case FIONBIO:
		if ((*(int *)data))
			atomic_set_int(&fp->f_flag, FNONBLOCK);
		else
			atomic_clear_int(&fp->f_flag, FNONBLOCK);
	case FIOASYNC:
		return (0);
	default:
		return (ENXIO);
	}
}