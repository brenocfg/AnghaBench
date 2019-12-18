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
struct pt_regs {int dummy; } ;
struct TYPE_2__ {scalar_t__ armed; scalar_t__* address; int /*<<< orphan*/ * opcode; scalar_t__ is_branch; } ;

/* Variables and functions */
 scalar_t__ BREAK_INSTR_SIZE ; 
 int /*<<< orphan*/  flush_icache_range (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  memcpy (void*,int /*<<< orphan*/ *,scalar_t__) ; 
 TYPE_1__ single_step_data ; 

__attribute__((used)) static void undo_single_step(struct pt_regs *regs)
{
	if (single_step_data.armed) {
		int i;

		for (i = 0; i < (single_step_data.is_branch ? 2 : 1); i++) {
			memcpy((void *) single_step_data.address[i],
				&single_step_data.opcode[i],
				BREAK_INSTR_SIZE);

			flush_icache_range(single_step_data.address[i],
				single_step_data.address[i] +
				BREAK_INSTR_SIZE);
		}
		single_step_data.armed = 0;
	}
}