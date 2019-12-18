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
struct TYPE_2__ {int size; struct cmd_clk_get_max_clk_id_response* data; } ;
struct tegra_bpmp_clk_message {TYPE_1__ rx; int /*<<< orphan*/  cmd; } ;
struct tegra_bpmp {int dummy; } ;
struct cmd_clk_get_max_clk_id_response {scalar_t__ max_id; } ;
typedef  int /*<<< orphan*/  response ;
typedef  int /*<<< orphan*/  msg ;

/* Variables and functions */
 int /*<<< orphan*/  CMD_CLK_GET_MAX_CLK_ID ; 
 int E2BIG ; 
 scalar_t__ INT_MAX ; 
 int /*<<< orphan*/  memset (struct tegra_bpmp_clk_message*,int /*<<< orphan*/ ,int) ; 
 int tegra_bpmp_clk_transfer (struct tegra_bpmp*,struct tegra_bpmp_clk_message*) ; 

__attribute__((used)) static int tegra_bpmp_clk_get_max_id(struct tegra_bpmp *bpmp)
{
	struct cmd_clk_get_max_clk_id_response response;
	struct tegra_bpmp_clk_message msg;
	int err;

	memset(&msg, 0, sizeof(msg));
	msg.cmd = CMD_CLK_GET_MAX_CLK_ID;
	msg.rx.data = &response;
	msg.rx.size = sizeof(response);

	err = tegra_bpmp_clk_transfer(bpmp, &msg);
	if (err < 0)
		return err;

	if (response.max_id > INT_MAX)
		return -E2BIG;

	return response.max_id;
}