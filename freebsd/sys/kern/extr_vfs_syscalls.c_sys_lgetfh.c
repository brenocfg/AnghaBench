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
struct lgetfh_args {int /*<<< orphan*/  fhp; int /*<<< orphan*/  fname; } ;

/* Variables and functions */
 int /*<<< orphan*/  AT_FDCWD ; 
 int /*<<< orphan*/  AT_SYMLINK_NOFOLLOW ; 
 int /*<<< orphan*/  UIO_USERSPACE ; 
 int kern_getfhat (struct thread*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int
sys_lgetfh(struct thread *td, struct lgetfh_args *uap)
{

	return (kern_getfhat(td, AT_SYMLINK_NOFOLLOW, AT_FDCWD, uap->fname,
	    UIO_USERSPACE, uap->fhp));
}