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
struct symlinkat_args {int /*<<< orphan*/  path2; int /*<<< orphan*/  fd; int /*<<< orphan*/  path1; } ;

/* Variables and functions */
 int /*<<< orphan*/  UIO_USERSPACE ; 
 int kern_symlinkat (struct thread*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int
sys_symlinkat(struct thread *td, struct symlinkat_args *uap)
{

	return (kern_symlinkat(td, uap->path1, uap->fd, uap->path2,
	    UIO_USERSPACE));
}