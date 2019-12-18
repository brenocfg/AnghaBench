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
struct tegra_bpmp_channel {int /*<<< orphan*/  index; TYPE_1__* bpmp; } ;
struct tegra210_bpmp {scalar_t__ arb_sema; } ;
struct TYPE_2__ {struct tegra210_bpmp* priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  MA_ACKD (int /*<<< orphan*/ ) ; 
 scalar_t__ SET_OFFSET ; 
 int /*<<< orphan*/  __raw_writel (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static int tegra210_bpmp_post_response(struct tegra_bpmp_channel *channel)
{
	struct tegra210_bpmp *priv = channel->bpmp->priv;

	__raw_writel(MA_ACKD(channel->index), priv->arb_sema + SET_OFFSET);

	return 0;
}