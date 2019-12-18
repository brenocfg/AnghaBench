#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct tegra_bpmp {TYPE_2__* soc; } ;
struct TYPE_4__ {TYPE_1__* ops; } ;
struct TYPE_3__ {int (* ring_doorbell ) (struct tegra_bpmp*) ;} ;

/* Variables and functions */
 int stub1 (struct tegra_bpmp*) ; 

__attribute__((used)) static int tegra_bpmp_ring_doorbell(struct tegra_bpmp *bpmp)
{
	return bpmp->soc->ops->ring_doorbell(bpmp);
}