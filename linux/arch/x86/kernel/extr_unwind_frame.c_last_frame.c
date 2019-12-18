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
struct unwind_state {int /*<<< orphan*/  task; } ;

/* Variables and functions */
 scalar_t__ task_pt_regs (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline unsigned long *last_frame(struct unwind_state *state)
{
	return (unsigned long *)task_pt_regs(state->task) - 2;
}