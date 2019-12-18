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
struct thread {int /*<<< orphan*/ * td_retval; } ;
struct getppid_args {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  kern_getppid (struct thread*) ; 

int
sys_getppid(struct thread *td, struct getppid_args *uap)
{

	td->td_retval[0] = kern_getppid(td);
	return (0);
}