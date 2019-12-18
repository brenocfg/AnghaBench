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
typedef  int resource_size_t ;

/* Variables and functions */
#define  LPC32XX_HS_UART1_BASE 130 
#define  LPC32XX_HS_UART2_BASE 129 
#define  LPC32XX_HS_UART7_BASE 128 
 int /*<<< orphan*/  LPC32XX_UARTCTL_CLOOP ; 
 int /*<<< orphan*/  WARN (int,char*,int) ; 
 int readl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  writel (int,int /*<<< orphan*/ ) ; 

void lpc32xx_loopback_set(resource_size_t mapbase, int state)
{
	int bit;
	u32 tmp;

	switch (mapbase) {
	case LPC32XX_HS_UART1_BASE:
		bit = 0;
		break;
	case LPC32XX_HS_UART2_BASE:
		bit = 1;
		break;
	case LPC32XX_HS_UART7_BASE:
		bit = 6;
		break;
	default:
		WARN(1, "lpc32xx_hs: Warning: Unknown port at %08x\n", mapbase);
		return;
	}

	tmp = readl(LPC32XX_UARTCTL_CLOOP);
	if (state)
		tmp |= (1 << bit);
	else
		tmp &= ~(1 << bit);
	writel(tmp, LPC32XX_UARTCTL_CLOOP);
}