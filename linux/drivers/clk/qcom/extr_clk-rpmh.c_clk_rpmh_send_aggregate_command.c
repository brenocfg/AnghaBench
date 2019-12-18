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
typedef  int u32 ;
struct tcs_cmd {int data; int /*<<< orphan*/  addr; int /*<<< orphan*/  member_0; } ;
struct clk_rpmh {int aggr_state; int res_on_val; int last_sent_aggr_state; TYPE_1__* peer; int /*<<< orphan*/  res_name; int /*<<< orphan*/  dev; int /*<<< orphan*/  res_addr; } ;
typedef  enum rpmh_state { ____Placeholder_rpmh_state } rpmh_state ;
struct TYPE_2__ {int last_sent_aggr_state; } ;

/* Variables and functions */
 int BIT (int) ; 
 int RPMH_ACTIVE_ONLY_STATE ; 
 int RPMH_SLEEP_STATE ; 
 int RPMH_WAKE_ONLY_STATE ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,char*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ has_state_changed (struct clk_rpmh*,int) ; 
 int rpmh_write_async (int /*<<< orphan*/ ,int,struct tcs_cmd*,int) ; 

__attribute__((used)) static int clk_rpmh_send_aggregate_command(struct clk_rpmh *c)
{
	struct tcs_cmd cmd = { 0 };
	u32 cmd_state, on_val;
	enum rpmh_state state = RPMH_SLEEP_STATE;
	int ret;

	cmd.addr = c->res_addr;
	cmd_state = c->aggr_state;
	on_val = c->res_on_val;

	for (; state <= RPMH_ACTIVE_ONLY_STATE; state++) {
		if (has_state_changed(c, state)) {
			if (cmd_state & BIT(state))
				cmd.data = on_val;

			ret = rpmh_write_async(c->dev, state, &cmd, 1);
			if (ret) {
				dev_err(c->dev, "set %s state of %s failed: (%d)\n",
					!state ? "sleep" :
					state == RPMH_WAKE_ONLY_STATE	?
					"wake" : "active", c->res_name, ret);
				return ret;
			}
		}
	}

	c->last_sent_aggr_state = c->aggr_state;
	c->peer->last_sent_aggr_state =  c->last_sent_aggr_state;

	return 0;
}