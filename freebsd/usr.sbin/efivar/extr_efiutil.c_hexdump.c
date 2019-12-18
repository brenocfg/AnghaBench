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

/* Variables and functions */
 int /*<<< orphan*/  printf (char*,...) ; 

void
hexdump(uint8_t *data, size_t datalen)
{
	size_t i;

	for (i = 0; i < datalen; i++) {
		if (i % 16 == 0) {
			if (i != 0)
				printf("\n");
			printf("%04x: ", (int)i);
		}
		printf("%02x ", data[i]);
	}
	printf("\n");
}