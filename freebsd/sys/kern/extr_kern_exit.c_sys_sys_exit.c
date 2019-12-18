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
struct sys_exit_args {int /*<<< orphan*/  rval; } ;

/* Variables and functions */
 int /*<<< orphan*/  exit1 (struct thread*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
sys_sys_exit(struct thread *td, struct sys_exit_args *uap)
{

	exit1(td, uap->rval, 0);
	/* NOTREACHED */
}