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
typedef  int uint8_t ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 unsigned int NVRAM_SIZE ; 
 int /*<<< orphan*/  OUTB_DELAY (int*,int) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ wait_operation_complete_amd (int*) ; 

__attribute__((used)) static int
write_bank_amd(device_t dev, uint8_t *bank, uint8_t *data)
{
	unsigned int i;

	for (i = 0; i < NVRAM_SIZE; i++) {
		/* Unlock 1 */
		OUTB_DELAY(bank + 0x555, 0xaa);
		/* Unlock 2 */
		OUTB_DELAY(bank + 0x2aa, 0x55);

		/* Write single word */
		OUTB_DELAY(bank + 0x555, 0xa0);
		OUTB_DELAY(bank + i, data[i]);
		if (wait_operation_complete_amd(bank) != 0) {
			device_printf(dev, "flash write timeout\n");
			return -1;
		}
	}

	/* Reset */
	OUTB_DELAY(bank, 0xf0);

	for (i = 0; i < NVRAM_SIZE; i++) {
		if (bank[i] != data[i]) {
			device_printf(dev, "flash write has failed\n");
			return -1;
		}
	}
	return 0;
}