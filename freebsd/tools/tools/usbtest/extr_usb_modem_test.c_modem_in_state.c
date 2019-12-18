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
typedef  char uint8_t ;
typedef  int uint32_t ;
struct TYPE_2__ {char in_last; int in_synced; int errors; int /*<<< orphan*/  c1; } ;

/* Variables and functions */
 TYPE_1__ modem ; 
 int /*<<< orphan*/  printf (char*,...) ; 

__attribute__((used)) static void
modem_in_state(uint8_t buf, uint32_t counter)
{
	if ((modem.in_last == 'O') && (buf == 'K')) {
		modem.c1++;
		modem.in_last = buf;
	} else if (buf == modem.in_last) {
		modem.c1++;
		modem.in_last++;
		modem.in_last %= 255;
		if (modem.in_synced == 0) {
			if (modem.errors < 64) {
				printf("Got sync\n");
			}
			modem.in_synced = 1;
		}
	} else {
		if (modem.in_synced) {
			if (modem.errors < 64) {
				printf("Lost sync @ %d, 0x%02x != 0x%02x\n",
				    counter % 512, buf, modem.in_last);
			}
			modem.in_synced = 0;
			modem.errors++;
		}
		modem.in_last = buf;
		modem.in_last++;
		modem.in_last %= 255;
	}
}