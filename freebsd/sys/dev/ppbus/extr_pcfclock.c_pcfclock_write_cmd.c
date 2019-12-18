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
struct pcfclock_data {int /*<<< orphan*/  dev; } ;
struct cdev {struct pcfclock_data* si_drv1; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  AFC_HI ; 
 int /*<<< orphan*/  AFC_LO ; 
 int /*<<< orphan*/  AUTOFEED_CLOCK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DELAY (int) ; 
 int /*<<< orphan*/  device_get_parent (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ppb_wdtr (int /*<<< orphan*/ ,unsigned char) ; 

__attribute__((used)) static void
pcfclock_write_cmd(struct cdev *dev, unsigned char command)
{
	struct pcfclock_data *sc = dev->si_drv1;
	device_t pcfclockdev = sc->dev;
	device_t ppbus = device_get_parent(pcfclockdev);
	unsigned char ctr = 14;
	char i;

	for (i = 0; i <= 7; i++) {
		ppb_wdtr(ppbus, i);
		AUTOFEED_CLOCK(i & 1 ? AFC_HI : AFC_LO);
		DELAY(3000);
	}
	ppb_wdtr(ppbus, command);
	AUTOFEED_CLOCK(AFC_LO);
	DELAY(3000);
	AUTOFEED_CLOCK(AFC_HI);
}