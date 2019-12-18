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
struct cardinfo {scalar_t__ csr_remap; } ;

/* Variables and functions */
 unsigned char LED_FLIP ; 
 scalar_t__ MEMCTRLCMD_LEDCTRL ; 
 unsigned char readb (scalar_t__) ; 
 int /*<<< orphan*/  writeb (unsigned char,scalar_t__) ; 

__attribute__((used)) static void set_led(struct cardinfo *card, int shift, unsigned char state)
{
	unsigned char led;

	led = readb(card->csr_remap + MEMCTRLCMD_LEDCTRL);
	if (state == LED_FLIP)
		led ^= (1<<shift);
	else {
		led &= ~(0x03 << shift);
		led |= (state << shift);
	}
	writeb(led, card->csr_remap + MEMCTRLCMD_LEDCTRL);

}