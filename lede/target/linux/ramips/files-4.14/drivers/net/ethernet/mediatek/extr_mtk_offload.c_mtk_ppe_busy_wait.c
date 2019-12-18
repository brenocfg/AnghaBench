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
typedef  int u32 ;
struct mtk_eth {int /*<<< orphan*/  rst_ppe; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int ETIMEDOUT ; 
 scalar_t__ HZ ; 
 int MTK_PPE_GLO_CFG_BUSY ; 
 int /*<<< orphan*/  MTK_REG_PPE_GLO_CFG ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 unsigned long jiffies ; 
 int mtk_r32 (struct mtk_eth*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  reset_control_reset (int /*<<< orphan*/ ) ; 
 scalar_t__ time_after (unsigned long,scalar_t__) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 

__attribute__((used)) static int mtk_ppe_busy_wait(struct mtk_eth *eth)
{
	unsigned long t_start = jiffies;
	u32 r = 0;

	while (1) {
		r = mtk_r32(eth, MTK_REG_PPE_GLO_CFG);
		if (!(r & MTK_PPE_GLO_CFG_BUSY))
			return 0;
		if (time_after(jiffies, t_start + HZ))
			break;
		usleep_range(10, 20);
	}

	dev_err(eth->dev, "ppe: table busy timeout - resetting\n");
	reset_control_reset(eth->rst_ppe);

	return -ETIMEDOUT;
}