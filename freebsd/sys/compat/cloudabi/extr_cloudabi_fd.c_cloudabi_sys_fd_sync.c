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
struct thread {int dummy; } ;
struct cloudabi_sys_fd_sync_args {int /*<<< orphan*/  fd; } ;

/* Variables and functions */
 int kern_fsync (struct thread*,int /*<<< orphan*/ ,int) ; 

int
cloudabi_sys_fd_sync(struct thread *td, struct cloudabi_sys_fd_sync_args *uap)
{

	return (kern_fsync(td, uap->fd, true));
}