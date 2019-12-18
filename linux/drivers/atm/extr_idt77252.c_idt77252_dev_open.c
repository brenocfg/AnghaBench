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
struct idt77252_dev {int /*<<< orphan*/  name; int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  IDT77252_BIT_INIT ; 
 int /*<<< orphan*/  IPRINTK (char*,int /*<<< orphan*/ ) ; 
 int SAR_CFG_FBIE ; 
 int SAR_CFG_PHYIE ; 
 int SAR_CFG_RAWIE ; 
 int SAR_CFG_RQFIE ; 
 int SAR_CFG_RXPTH ; 
 int SAR_CFG_TMOIE ; 
 int SAR_CFG_TXEN ; 
 int SAR_CFG_TXINT ; 
 int SAR_CFG_TXSFI ; 
 int SAR_CFG_TXUIE ; 
 int SAR_CFG_VPECA ; 
 int /*<<< orphan*/  SAR_REG_CFG ; 
 int SAR_RX_DELAY ; 
 scalar_t__ open_card_oam (struct idt77252_dev*) ; 
 scalar_t__ open_card_ubr0 (struct idt77252_dev*) ; 
 int /*<<< orphan*/  printk (char*,int /*<<< orphan*/ ) ; 
 int readl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  writel (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
idt77252_dev_open(struct idt77252_dev *card)
{
	u32 conf;

	if (!test_bit(IDT77252_BIT_INIT, &card->flags)) {
		printk("%s: SAR not yet initialized.\n", card->name);
		return -1;
	}

	conf = SAR_CFG_RXPTH|	/* enable receive path                  */
	    SAR_RX_DELAY |	/* interrupt on complete PDU		*/
	    SAR_CFG_RAWIE |	/* interrupt enable on raw cells        */
	    SAR_CFG_RQFIE |	/* interrupt on RSQ almost full         */
	    SAR_CFG_TMOIE |	/* interrupt on timer overflow          */
	    SAR_CFG_FBIE |	/* interrupt on low free buffers        */
	    SAR_CFG_TXEN |	/* transmit operation enable            */
	    SAR_CFG_TXINT |	/* interrupt on transmit status         */
	    SAR_CFG_TXUIE |	/* interrupt on transmit underrun       */
	    SAR_CFG_TXSFI |	/* interrupt on TSQ almost full         */
	    SAR_CFG_PHYIE	/* enable PHY interrupts		*/
	    ;

#ifdef CONFIG_ATM_IDT77252_RCV_ALL
	/* Test RAW cell receive. */
	conf |= SAR_CFG_VPECA;
#endif

	writel(readl(SAR_REG_CFG) | conf, SAR_REG_CFG);

	if (open_card_oam(card)) {
		printk("%s: Error initializing OAM.\n", card->name);
		return -1;
	}

	if (open_card_ubr0(card)) {
		printk("%s: Error initializing UBR0.\n", card->name);
		return -1;
	}

	IPRINTK("%s: opened IDT77252 ABR SAR.\n", card->name);
	return 0;
}