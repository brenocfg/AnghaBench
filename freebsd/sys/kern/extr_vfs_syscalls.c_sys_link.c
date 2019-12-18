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
struct link_args {int /*<<< orphan*/  link; int /*<<< orphan*/  path; } ;

/* Variables and functions */
 int /*<<< orphan*/  AT_FDCWD ; 
 int /*<<< orphan*/  FOLLOW ; 
 int /*<<< orphan*/  UIO_USERSPACE ; 
 int kern_linkat (struct thread*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int
sys_link(struct thread *td, struct link_args *uap)
{

	return (kern_linkat(td, AT_FDCWD, AT_FDCWD, uap->path, uap->link,
	    UIO_USERSPACE, FOLLOW));
}