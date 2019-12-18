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
struct funlinkat_args {int /*<<< orphan*/  flag; int /*<<< orphan*/  fd; int /*<<< orphan*/  path; int /*<<< orphan*/  dfd; } ;

/* Variables and functions */
 int /*<<< orphan*/  UIO_USERSPACE ; 
 int kern_funlinkat_ex (struct thread*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int
sys_funlinkat(struct thread *td, struct funlinkat_args *uap)
{

	return (kern_funlinkat_ex(td, uap->dfd, uap->path, uap->fd, uap->flag,
	    UIO_USERSPACE, 0));
}