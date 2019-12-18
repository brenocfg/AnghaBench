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
struct show_state {int* printed; TYPE_1__* rule; } ;
typedef  int /*<<< orphan*/  ipfw_insn ;
struct TYPE_2__ {int /*<<< orphan*/  const* cmd; } ;

/* Variables and functions */

__attribute__((used)) static void
mark_printed(struct show_state *state, const ipfw_insn *cmd)
{

	state->printed[cmd - state->rule->cmd] = 1;
}