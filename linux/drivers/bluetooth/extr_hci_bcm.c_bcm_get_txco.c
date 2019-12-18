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
struct device {int dummy; } ;
struct clk {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  EPROBE_DEFER ; 
 int /*<<< orphan*/  IS_ERR (struct clk*) ; 
 int /*<<< orphan*/  PTR_ERR (struct clk*) ; 
 struct clk* devm_clk_get (struct device*,char*) ; 

__attribute__((used)) static struct clk *bcm_get_txco(struct device *dev)
{
	struct clk *clk;

	/* New explicit name */
	clk = devm_clk_get(dev, "txco");
	if (!IS_ERR(clk) || PTR_ERR(clk) == -EPROBE_DEFER)
		return clk;

	/* Deprecated name */
	clk = devm_clk_get(dev, "extclk");
	if (!IS_ERR(clk) || PTR_ERR(clk) == -EPROBE_DEFER)
		return clk;

	/* Original code used no name at all */
	return devm_clk_get(dev, NULL);
}