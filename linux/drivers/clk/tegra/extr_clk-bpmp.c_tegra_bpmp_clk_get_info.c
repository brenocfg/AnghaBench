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
struct TYPE_2__ {int size; struct cmd_clk_get_all_info_response* data; } ;
struct tegra_bpmp_clk_message {unsigned int id; TYPE_1__ rx; int /*<<< orphan*/  cmd; } ;
struct tegra_bpmp_clk_info {unsigned int num_parents; int /*<<< orphan*/  flags; int /*<<< orphan*/ * parents; int /*<<< orphan*/  name; } ;
struct tegra_bpmp {int dummy; } ;
struct cmd_clk_get_all_info_response {unsigned int num_parents; int /*<<< orphan*/  flags; int /*<<< orphan*/ * parents; int /*<<< orphan*/  name; } ;
typedef  int /*<<< orphan*/  response ;
typedef  int /*<<< orphan*/  msg ;

/* Variables and functions */
 int /*<<< orphan*/  CMD_CLK_GET_ALL_INFO ; 
 int /*<<< orphan*/  MRQ_CLK_NAME_MAXLEN ; 
 int /*<<< orphan*/  memset (struct tegra_bpmp_clk_message*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int tegra_bpmp_clk_transfer (struct tegra_bpmp*,struct tegra_bpmp_clk_message*) ; 

__attribute__((used)) static int tegra_bpmp_clk_get_info(struct tegra_bpmp *bpmp, unsigned int id,
				   struct tegra_bpmp_clk_info *info)
{
	struct cmd_clk_get_all_info_response response;
	struct tegra_bpmp_clk_message msg;
	unsigned int i;
	int err;

	memset(&msg, 0, sizeof(msg));
	msg.cmd = CMD_CLK_GET_ALL_INFO;
	msg.id = id;
	msg.rx.data = &response;
	msg.rx.size = sizeof(response);

	err = tegra_bpmp_clk_transfer(bpmp, &msg);
	if (err < 0)
		return err;

	strlcpy(info->name, response.name, MRQ_CLK_NAME_MAXLEN);
	info->num_parents = response.num_parents;

	for (i = 0; i < info->num_parents; i++)
		info->parents[i] = response.parents[i];

	info->flags = response.flags;

	return 0;
}