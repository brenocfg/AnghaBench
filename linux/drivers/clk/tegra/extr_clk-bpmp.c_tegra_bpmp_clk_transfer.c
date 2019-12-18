#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {scalar_t__ ret; int /*<<< orphan*/  size; int /*<<< orphan*/  data; } ;
struct TYPE_6__ {int size; struct tegra_bpmp_message* data; } ;
struct tegra_bpmp_message {int cmd_and_id; TYPE_4__ rx; TYPE_2__ tx; int /*<<< orphan*/  mrq; } ;
struct TYPE_7__ {int /*<<< orphan*/  size; int /*<<< orphan*/  data; } ;
struct TYPE_5__ {int /*<<< orphan*/  size; int /*<<< orphan*/  data; } ;
struct tegra_bpmp_clk_message {int cmd; int id; TYPE_3__ rx; TYPE_1__ tx; } ;
struct tegra_bpmp {int dummy; } ;
struct mrq_clk_request {int cmd_and_id; TYPE_4__ rx; TYPE_2__ tx; int /*<<< orphan*/  mrq; } ;
typedef  int /*<<< orphan*/  request ;
typedef  int /*<<< orphan*/  msg ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  MRQ_CLK ; 
 int /*<<< orphan*/  memcpy (void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct tegra_bpmp_message*,int /*<<< orphan*/ ,int) ; 
 int tegra_bpmp_transfer (struct tegra_bpmp*,struct tegra_bpmp_message*) ; 

__attribute__((used)) static int tegra_bpmp_clk_transfer(struct tegra_bpmp *bpmp,
				   const struct tegra_bpmp_clk_message *clk)
{
	struct mrq_clk_request request;
	struct tegra_bpmp_message msg;
	void *req = &request;
	int err;

	memset(&request, 0, sizeof(request));
	request.cmd_and_id = (clk->cmd << 24) | clk->id;

	/*
	 * The mrq_clk_request structure has an anonymous union at offset 4
	 * that contains all possible sub-command structures. Copy the data
	 * to that union. Ideally we'd be able to refer to it by name, but
	 * doing so would require changing the ABI header and increase the
	 * maintenance burden.
	 */
	memcpy(req + 4, clk->tx.data, clk->tx.size);

	memset(&msg, 0, sizeof(msg));
	msg.mrq = MRQ_CLK;
	msg.tx.data = &request;
	msg.tx.size = sizeof(request);
	msg.rx.data = clk->rx.data;
	msg.rx.size = clk->rx.size;

	err = tegra_bpmp_transfer(bpmp, &msg);
	if (err < 0)
		return err;
	else if (msg.rx.ret < 0)
		return -EINVAL;

	return 0;
}