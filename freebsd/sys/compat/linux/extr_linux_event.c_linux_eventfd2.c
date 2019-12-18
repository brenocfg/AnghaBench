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
struct linux_eventfd2_args {int flags; int /*<<< orphan*/  initval; } ;

/* Variables and functions */
 int EINVAL ; 
 int LINUX_EFD_SEMAPHORE ; 
 int LINUX_O_CLOEXEC ; 
 int LINUX_O_NONBLOCK ; 
 int eventfd_create (struct thread*,int /*<<< orphan*/ ,int) ; 

int
linux_eventfd2(struct thread *td, struct linux_eventfd2_args *args)
{

	if ((args->flags & ~(LINUX_O_CLOEXEC|LINUX_O_NONBLOCK|LINUX_EFD_SEMAPHORE)) != 0)
		return (EINVAL);

	return (eventfd_create(td, args->initval, args->flags));
}