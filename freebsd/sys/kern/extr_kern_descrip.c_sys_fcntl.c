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
struct fcntl_args {int /*<<< orphan*/  arg; int /*<<< orphan*/  cmd; int /*<<< orphan*/  fd; } ;

/* Variables and functions */
 int kern_fcntl_freebsd (struct thread*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int
sys_fcntl(struct thread *td, struct fcntl_args *uap)
{

	return (kern_fcntl_freebsd(td, uap->fd, uap->cmd, uap->arg));
}