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
struct linux_mprotect_args {int /*<<< orphan*/  prot; int /*<<< orphan*/  len; int /*<<< orphan*/  addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  PTROUT (int /*<<< orphan*/ ) ; 
 int linux_mprotect_common (struct thread*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int
linux_mprotect(struct thread *td, struct linux_mprotect_args *uap)
{

	return (linux_mprotect_common(td, PTROUT(uap->addr), uap->len,
	    uap->prot));
}