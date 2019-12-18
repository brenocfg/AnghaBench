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
typedef  int u8 ;
typedef  int u32 ;
struct charlcd {scalar_t__ irq; scalar_t__ virtbase; } ;

/* Variables and functions */
 scalar_t__ CHAR_RAW ; 
 int /*<<< orphan*/  CHAR_RAW_CLEAR ; 
 int CHAR_RAW_VALID ; 
 scalar_t__ CHAR_RD ; 
 int /*<<< orphan*/  charlcd_wait_complete_irq (struct charlcd*) ; 
 int /*<<< orphan*/  msleep (int) ; 
 int readl (scalar_t__) ; 
 int /*<<< orphan*/  udelay (int) ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static u8 charlcd_4bit_read_char(struct charlcd *lcd)
{
	u8 data;
	u32 val;
	int i;

	/* If we can, use an IRQ to wait for the data, else poll */
	if (lcd->irq >= 0)
		charlcd_wait_complete_irq(lcd);
	else {
		i = 0;
		val = 0;
		while (!(val & CHAR_RAW_VALID) && i < 10) {
			udelay(100);
			val = readl(lcd->virtbase + CHAR_RAW);
			i++;
		}

		writel(CHAR_RAW_CLEAR, lcd->virtbase + CHAR_RAW);
	}
	msleep(1);

	/* Read the 4 high bits of the data */
	data = readl(lcd->virtbase + CHAR_RD) & 0xf0;

	/*
	 * The second read for the low bits does not trigger an IRQ
	 * so in this case we have to poll for the 4 lower bits
	 */
	i = 0;
	val = 0;
	while (!(val & CHAR_RAW_VALID) && i < 10) {
		udelay(100);
		val = readl(lcd->virtbase + CHAR_RAW);
		i++;
	}
	writel(CHAR_RAW_CLEAR, lcd->virtbase + CHAR_RAW);
	msleep(1);

	/* Read the 4 low bits of the data */
	data |= (readl(lcd->virtbase + CHAR_RD) >> 4) & 0x0f;

	return data;
}