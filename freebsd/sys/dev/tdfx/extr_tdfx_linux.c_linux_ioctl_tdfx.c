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
struct thread {int /*<<< orphan*/  td_ucred; } ;
struct linux_ioctl_args {int cmd; scalar_t__ arg; int /*<<< orphan*/  fd; } ;
struct file {int dummy; } ;
typedef  int /*<<< orphan*/  d_pio ;
typedef  int /*<<< orphan*/  cap_rights_t ;
typedef  int /*<<< orphan*/  caddr_t ;

/* Variables and functions */
 int /*<<< orphan*/  CAP_IOCTL ; 
 int /*<<< orphan*/  cap_rights_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  copyin (int /*<<< orphan*/ ,char**,int) ; 
 int /*<<< orphan*/  fdrop (struct file*,struct thread*) ; 
 int fget (struct thread*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct file**) ; 
 int fo_ioctl (struct file*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct thread*) ; 

__attribute__((used)) static int
linux_ioctl_tdfx(struct thread *td, struct linux_ioctl_args* args)
{
   cap_rights_t rights;
   int error = 0;
   u_long cmd = args->cmd & 0xffff;

   /* The structure passed to ioctl has two shorts, one int
      and one void*. */
   char d_pio[2*sizeof(short) + sizeof(int) + sizeof(void*)];

   struct file *fp;

   error = fget(td, args->fd, cap_rights_init(&rights, CAP_IOCTL), &fp);
   if (error != 0)
	   return (error);
   /* We simply copy the data and send it right to ioctl */
   copyin((caddr_t)args->arg, &d_pio, sizeof(d_pio));
   error = fo_ioctl(fp, cmd, (caddr_t)&d_pio, td->td_ucred, td);
   fdrop(fp, td);
   return error;
}