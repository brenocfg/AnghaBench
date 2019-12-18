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
struct rcar_dmac {int dummy; } ;
struct platform_device {int dummy; } ;

/* Variables and functions */
 struct rcar_dmac* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  rcar_dmac_stop_all_chan (struct rcar_dmac*) ; 

__attribute__((used)) static void rcar_dmac_shutdown(struct platform_device *pdev)
{
	struct rcar_dmac *dmac = platform_get_drvdata(pdev);

	rcar_dmac_stop_all_chan(dmac);
}