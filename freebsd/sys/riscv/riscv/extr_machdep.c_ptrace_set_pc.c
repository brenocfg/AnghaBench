#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u_long ;
struct thread {TYPE_1__* td_frame; } ;
struct TYPE_2__ {int /*<<< orphan*/  tf_sepc; } ;

/* Variables and functions */

int
ptrace_set_pc(struct thread *td, u_long addr)
{

	td->td_frame->tf_sepc = addr;
	return (0);
}