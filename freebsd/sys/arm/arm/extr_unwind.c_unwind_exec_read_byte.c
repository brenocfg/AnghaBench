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
typedef  int uint8_t ;
struct unwind_state {int* insn; int byte; int /*<<< orphan*/  entries; } ;

/* Variables and functions */

__attribute__((used)) static uint8_t
unwind_exec_read_byte(struct unwind_state *state)
{
	uint8_t insn;

	/* Read the unwind instruction */
	insn = (*state->insn) >> (state->byte * 8);

	/* Update the location of the next instruction */
	if (state->byte == 0) {
		state->byte = 3;
		state->insn++;
		state->entries--;
	} else
		state->byte--;

	return insn;
}