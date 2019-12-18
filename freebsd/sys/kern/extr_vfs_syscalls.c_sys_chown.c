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
struct chown_args {int /*<<< orphan*/  gid; int /*<<< orphan*/  uid; int /*<<< orphan*/  path; } ;

/* Variables and functions */
 int /*<<< orphan*/  AT_FDCWD ; 
 int /*<<< orphan*/  UIO_USERSPACE ; 
 int kern_fchownat (struct thread*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int
sys_chown(struct thread *td, struct chown_args *uap)
{

	return (kern_fchownat(td, AT_FDCWD, uap->path, UIO_USERSPACE, uap->uid,
	    uap->gid, 0));
}