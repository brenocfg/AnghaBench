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
struct amba_device {int /*<<< orphan*/  pclk; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clk_get (int /*<<< orphan*/ *,char*) ; 
 int clk_prepare_enable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clk_put (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int amba_get_enable_pclk(struct amba_device *pcdev)
{
	int ret;

	pcdev->pclk = clk_get(&pcdev->dev, "apb_pclk");
	if (IS_ERR(pcdev->pclk))
		return PTR_ERR(pcdev->pclk);

	ret = clk_prepare_enable(pcdev->pclk);
	if (ret)
		clk_put(pcdev->pclk);

	return ret;
}