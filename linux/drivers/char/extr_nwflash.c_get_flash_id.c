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

/* Variables and functions */
 scalar_t__ FLASH_BASE ; 
 unsigned int volatile KFLASH_ID4 ; 
 int /*<<< orphan*/  KFLASH_SIZE4 ; 
 int /*<<< orphan*/  gbFlashSize ; 
 unsigned int inb (int) ; 
 int /*<<< orphan*/  kick_open () ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static int get_flash_id(void)
{
	volatile unsigned int c1, c2;

	/*
	 * try to get flash chip ID
	 */
	kick_open();
	c2 = inb(0x80);
	*(volatile unsigned char *) (FLASH_BASE + 0x8000) = 0x90;
	udelay(15);
	c1 = *(volatile unsigned char *) FLASH_BASE;
	c2 = inb(0x80);

	/*
	 * on 4 Meg flash the second byte is actually at offset 2...
	 */
	if (c1 == 0xB0)
		c2 = *(volatile unsigned char *) (FLASH_BASE + 2);
	else
		c2 = *(volatile unsigned char *) (FLASH_BASE + 1);

	c2 += (c1 << 8);

	/*
	 * set it back to read mode
	 */
	*(volatile unsigned char *) (FLASH_BASE + 0x8000) = 0xFF;

	if (c2 == KFLASH_ID4)
		gbFlashSize = KFLASH_SIZE4;

	return c2;
}