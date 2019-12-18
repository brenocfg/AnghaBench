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
struct linux_mincore_args {int start; int /*<<< orphan*/  vec; int /*<<< orphan*/  len; } ;

/* Variables and functions */
 int EINVAL ; 
 int PAGE_MASK ; 
 int kern_mincore (struct thread*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int
linux_mincore(struct thread *td, struct linux_mincore_args *args)
{

	/* Needs to be page-aligned */
	if (args->start & PAGE_MASK)
		return (EINVAL);
	return (kern_mincore(td, args->start, args->len, args->vec));
}