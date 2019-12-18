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
struct rmdir_args {int /*<<< orphan*/  path; } ;

/* Variables and functions */
 int /*<<< orphan*/  AT_FDCWD ; 
 int /*<<< orphan*/  FD_NONE ; 
 int /*<<< orphan*/  UIO_USERSPACE ; 
 int kern_frmdirat (struct thread*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int
sys_rmdir(struct thread *td, struct rmdir_args *uap)
{

	return (kern_frmdirat(td, AT_FDCWD, uap->path, FD_NONE, UIO_USERSPACE,
	    0));
}