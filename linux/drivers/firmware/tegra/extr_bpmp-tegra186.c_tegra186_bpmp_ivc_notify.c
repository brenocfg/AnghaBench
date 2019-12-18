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
struct tegra_ivc {int dummy; } ;
struct tegra_bpmp {struct tegra186_bpmp* priv; } ;
struct TYPE_2__ {int /*<<< orphan*/ * channel; } ;
struct tegra186_bpmp {TYPE_1__ mbox; } ;

/* Variables and functions */
 scalar_t__ WARN_ON (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tegra186_bpmp_ring_doorbell (struct tegra_bpmp*) ; 

__attribute__((used)) static void tegra186_bpmp_ivc_notify(struct tegra_ivc *ivc, void *data)
{
	struct tegra_bpmp *bpmp = data;
	struct tegra186_bpmp *priv = bpmp->priv;

	if (WARN_ON(priv->mbox.channel == NULL))
		return;

	tegra186_bpmp_ring_doorbell(bpmp);
}