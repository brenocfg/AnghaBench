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
struct ag71xx_platform_data {scalar_t__ is_ar724x; scalar_t__ use_flow_control; } ;
struct ag71xx {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  AG71XX_REG_FIFO_CFG0 ; 
 int /*<<< orphan*/  AG71XX_REG_FIFO_CFG1 ; 
 int /*<<< orphan*/  AG71XX_REG_FIFO_CFG2 ; 
 int /*<<< orphan*/  AG71XX_REG_FIFO_CFG4 ; 
 int /*<<< orphan*/  AG71XX_REG_FIFO_CFG5 ; 
 int /*<<< orphan*/  AG71XX_REG_MAC_CFG1 ; 
 int /*<<< orphan*/  AG71XX_REG_MAC_CFG2 ; 
 int /*<<< orphan*/  AG71XX_REG_MAC_MFL ; 
 int FIFO_CFG0_INIT ; 
 int FIFO_CFG4_INIT ; 
 int FIFO_CFG5_INIT ; 
 int MAC_CFG1_INIT ; 
 int MAC_CFG1_RFC ; 
 int MAC_CFG1_TFC ; 
 int MAC_CFG2_LEN_CHECK ; 
 int MAC_CFG2_PAD_CRC_EN ; 
 struct ag71xx_platform_data* ag71xx_get_pdata (struct ag71xx*) ; 
 int /*<<< orphan*/  ag71xx_sb (struct ag71xx*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ag71xx_wr (struct ag71xx*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void ag71xx_hw_setup(struct ag71xx *ag)
{
	struct ag71xx_platform_data *pdata = ag71xx_get_pdata(ag);
	u32 init = MAC_CFG1_INIT;

	/* setup MAC configuration registers */
	if (pdata->use_flow_control)
		init |= MAC_CFG1_TFC | MAC_CFG1_RFC;
	ag71xx_wr(ag, AG71XX_REG_MAC_CFG1, init);

	ag71xx_sb(ag, AG71XX_REG_MAC_CFG2,
		  MAC_CFG2_PAD_CRC_EN | MAC_CFG2_LEN_CHECK);

	/* setup max frame length to zero */
	ag71xx_wr(ag, AG71XX_REG_MAC_MFL, 0);

	/* setup FIFO configuration registers */
	ag71xx_wr(ag, AG71XX_REG_FIFO_CFG0, FIFO_CFG0_INIT);
	if (pdata->is_ar724x) {
		ag71xx_wr(ag, AG71XX_REG_FIFO_CFG1, 0x0010ffff);
		ag71xx_wr(ag, AG71XX_REG_FIFO_CFG2, 0x015500aa);
	} else {
		ag71xx_wr(ag, AG71XX_REG_FIFO_CFG1, 0x0fff0000);
		ag71xx_wr(ag, AG71XX_REG_FIFO_CFG2, 0x00001fff);
	}
	ag71xx_wr(ag, AG71XX_REG_FIFO_CFG4, FIFO_CFG4_INIT);
	ag71xx_wr(ag, AG71XX_REG_FIFO_CFG5, FIFO_CFG5_INIT);
}