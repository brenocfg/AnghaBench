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

/* Variables and functions */
 int /*<<< orphan*/  PROC_ACTION (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ptrace_single_step (struct thread*) ; 

int
proc_sstep(struct thread *td)
{

	PROC_ACTION(ptrace_single_step(td));
}