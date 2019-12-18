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
typedef  int u32 ;
struct net_device {int /*<<< orphan*/  dev_addr; int /*<<< orphan*/  mtu; } ;
struct ag71xx_platform_data {int reset_bit; } ;
struct TYPE_2__ {int descs_dma; scalar_t__ dirty; scalar_t__ curr; } ;
struct ag71xx {TYPE_1__ tx_ring; struct net_device* dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  AG71XX_REG_MAC_MFL ; 
 int /*<<< orphan*/  AG71XX_REG_MII_CFG ; 
 int /*<<< orphan*/  AG71XX_REG_RX_DESC ; 
 int /*<<< orphan*/  AG71XX_REG_TX_DESC ; 
 int AR71XX_RESET_GE0_MAC ; 
 int AR71XX_RESET_GE1_MAC ; 
 int /*<<< orphan*/  ag71xx_dma_reset (struct ag71xx*) ; 
 struct ag71xx_platform_data* ag71xx_get_pdata (struct ag71xx*) ; 
 int /*<<< orphan*/  ag71xx_hw_set_macaddr (struct ag71xx*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ag71xx_hw_setup (struct ag71xx*) ; 
 int /*<<< orphan*/  ag71xx_hw_stop (struct ag71xx*) ; 
 int ag71xx_max_frame_len (int /*<<< orphan*/ ) ; 
 int ag71xx_rr (struct ag71xx*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ag71xx_tx_packets (struct ag71xx*,int) ; 
 int /*<<< orphan*/  ag71xx_wr (struct ag71xx*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ath79_device_reset_clear (int) ; 
 int /*<<< orphan*/  ath79_device_reset_set (int) ; 
 int /*<<< orphan*/  netdev_reset_queue (struct net_device*) ; 
 int /*<<< orphan*/  udelay (int) ; 
 int /*<<< orphan*/  wmb () ; 

__attribute__((used)) static void ag71xx_fast_reset(struct ag71xx *ag)
{
	struct ag71xx_platform_data *pdata = ag71xx_get_pdata(ag);
	struct net_device *dev = ag->dev;
	u32 reset_mask = pdata->reset_bit;
	u32 rx_ds;
	u32 mii_reg;

	reset_mask &= AR71XX_RESET_GE0_MAC | AR71XX_RESET_GE1_MAC;

	ag71xx_hw_stop(ag);
	wmb();

	mii_reg = ag71xx_rr(ag, AG71XX_REG_MII_CFG);
	rx_ds = ag71xx_rr(ag, AG71XX_REG_RX_DESC);

	ag71xx_tx_packets(ag, true);

	ath79_device_reset_set(reset_mask);
	udelay(10);
	ath79_device_reset_clear(reset_mask);
	udelay(10);

	ag71xx_dma_reset(ag);
	ag71xx_hw_setup(ag);
	ag->tx_ring.curr = 0;
	ag->tx_ring.dirty = 0;
	netdev_reset_queue(ag->dev);

	/* setup max frame length */
	ag71xx_wr(ag, AG71XX_REG_MAC_MFL,
		  ag71xx_max_frame_len(ag->dev->mtu));

	ag71xx_wr(ag, AG71XX_REG_RX_DESC, rx_ds);
	ag71xx_wr(ag, AG71XX_REG_TX_DESC, ag->tx_ring.descs_dma);
	ag71xx_wr(ag, AG71XX_REG_MII_CFG, mii_reg);

	ag71xx_hw_set_macaddr(ag, dev->dev_addr);
}