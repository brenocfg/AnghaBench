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
struct renameat_args {int /*<<< orphan*/  new; int /*<<< orphan*/  newfd; int /*<<< orphan*/  old; int /*<<< orphan*/  oldfd; } ;

/* Variables and functions */
 int /*<<< orphan*/  UIO_USERSPACE ; 
 int kern_renameat (struct thread*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int
sys_renameat(struct thread *td, struct renameat_args *uap)
{

	return (kern_renameat(td, uap->oldfd, uap->old, uap->newfd, uap->new,
	    UIO_USERSPACE));
}