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
struct rk_crypto_info {int /*<<< orphan*/  sclk; int /*<<< orphan*/  aclk; int /*<<< orphan*/  hclk; int /*<<< orphan*/  dmaclk; } ;

/* Variables and functions */
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void rk_crypto_disable_clk(struct rk_crypto_info *dev)
{
	clk_disable_unprepare(dev->dmaclk);
	clk_disable_unprepare(dev->hclk);
	clk_disable_unprepare(dev->aclk);
	clk_disable_unprepare(dev->sclk);
}