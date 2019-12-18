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
struct TYPE_4__ {TYPE_1__* of_node; } ;
struct platform_device {TYPE_2__ dev; } ;
struct TYPE_3__ {int /*<<< orphan*/  parent; } ;

/* Variables and functions */
 int cp110_syscon_common_probe (struct platform_device*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int cp110_clk_probe(struct platform_device *pdev)
{
	return cp110_syscon_common_probe(pdev, pdev->dev.of_node->parent);
}