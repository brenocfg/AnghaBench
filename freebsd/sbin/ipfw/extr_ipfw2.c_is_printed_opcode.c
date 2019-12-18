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
typedef  int /*<<< orphan*/  uint8_t ;
struct show_state {TYPE_1__* rule; int /*<<< orphan*/ * printed; } ;
typedef  int /*<<< orphan*/  ipfw_insn ;
struct TYPE_2__ {int /*<<< orphan*/  const* cmd; } ;

/* Variables and functions */

__attribute__((used)) static uint8_t
is_printed_opcode(struct show_state *state, const ipfw_insn *cmd)
{

	return (state->printed[cmd - state->rule->cmd]);
}