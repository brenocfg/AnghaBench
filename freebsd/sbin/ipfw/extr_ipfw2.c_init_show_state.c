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
typedef  int /*<<< orphan*/  uint8_t ;
struct show_state {scalar_t__ or_block; scalar_t__ proto; scalar_t__ flags; int /*<<< orphan*/ * eaction; struct ip_fw_rule* rule; int /*<<< orphan*/ * printed; } ;
struct ip_fw_rule {int /*<<< orphan*/  cmd_len; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/ * calloc (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
init_show_state(struct show_state *state, struct ip_fw_rule *rule)
{

	state->printed = calloc(rule->cmd_len, sizeof(uint8_t));
	if (state->printed == NULL)
		return (ENOMEM);
	state->rule = rule;
	state->eaction = NULL;
	state->flags = 0;
	state->proto = 0;
	state->or_block = 0;
	return (0);
}