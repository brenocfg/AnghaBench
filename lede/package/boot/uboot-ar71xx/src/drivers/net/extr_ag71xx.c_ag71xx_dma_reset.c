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
struct ag71xx {TYPE_1__* dev; } ;
struct TYPE_2__ {char* name; } ;

/* Variables and functions */
 int /*<<< orphan*/  AG71XX_REG_RX_CTRL ; 
 int /*<<< orphan*/  AG71XX_REG_RX_DESC ; 
 int /*<<< orphan*/  AG71XX_REG_RX_STATUS ; 
 int /*<<< orphan*/  AG71XX_REG_TX_CTRL ; 
 int /*<<< orphan*/  AG71XX_REG_TX_DESC ; 
 int /*<<< orphan*/  AG71XX_REG_TX_STATUS ; 
 int /*<<< orphan*/  DBG (char*,char*,int,int) ; 
 int RX_STATUS_BE ; 
 int RX_STATUS_OF ; 
 int RX_STATUS_PR ; 
 int TX_STATUS_BE ; 
 int TX_STATUS_PS ; 
 int TX_STATUS_UR ; 
 int ag71xx_rr (struct ag71xx*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ag71xx_wr (struct ag71xx*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  printf (char*,char*,int) ; 

__attribute__((used)) static void ag71xx_dma_reset(struct ag71xx *ag)
{
	u32 val;
	int i;

	DBG("%s: txdesc reg: 0x%08x rxdesc reg: 0x%08x\n",
			ag->dev->name,
			ag71xx_rr(ag, AG71XX_REG_TX_DESC),
			ag71xx_rr(ag, AG71XX_REG_RX_DESC));
	
	/* stop RX and TX */
	ag71xx_wr(ag, AG71XX_REG_RX_CTRL, 0);
	ag71xx_wr(ag, AG71XX_REG_TX_CTRL, 0);

	/* clear descriptor addresses */
	ag71xx_wr(ag, AG71XX_REG_TX_DESC, 0);
	ag71xx_wr(ag, AG71XX_REG_RX_DESC, 0);

	/* clear pending RX/TX interrupts */
	for (i = 0; i < 256; i++) {
		ag71xx_wr(ag, AG71XX_REG_RX_STATUS, RX_STATUS_PR);
		ag71xx_wr(ag, AG71XX_REG_TX_STATUS, TX_STATUS_PS);
	}

	/* clear pending errors */
	ag71xx_wr(ag, AG71XX_REG_RX_STATUS, RX_STATUS_BE | RX_STATUS_OF);
	ag71xx_wr(ag, AG71XX_REG_TX_STATUS, TX_STATUS_BE | TX_STATUS_UR);

	val = ag71xx_rr(ag, AG71XX_REG_RX_STATUS);
	if (val)
		printf("%s: unable to clear DMA Rx status: %08x\n",
			ag->dev->name, val);

	val = ag71xx_rr(ag, AG71XX_REG_TX_STATUS);

	/* mask out reserved bits */
	val &= ~0xff000000;

	if (val)
		printf("%s: unable to clear DMA Tx status: %08x\n",
			ag->dev->name, val);
}