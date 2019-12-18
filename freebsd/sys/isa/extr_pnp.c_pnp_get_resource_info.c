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
typedef  int u_char ;

/* Variables and functions */
 int /*<<< orphan*/  DELAY (int) ; 
 int /*<<< orphan*/  PNP_RESOURCE_DATA ; 
 int /*<<< orphan*/  PNP_STATUS ; 
 int /*<<< orphan*/  _PNP_ADDRESS ; 
 int inb (int) ; 
 int /*<<< orphan*/  outb (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int pnp_rd_port ; 
 int /*<<< orphan*/  printf (char*) ; 

__attribute__((used)) static int
pnp_get_resource_info(u_char *buffer, int len)
{
	int i, j, count;
	u_char temp;

	count = 0;
	for (i = 0; i < len; i++) {
		outb(_PNP_ADDRESS, PNP_STATUS);
		for (j = 0; j < 100; j++) {
			if ((inb((pnp_rd_port << 2) | 0x3)) & 0x1)
				break;
			DELAY(10);
		}
		if (j == 100) {
			printf("PnP device failed to report resource data\n");
			return (count);
		}
		outb(_PNP_ADDRESS, PNP_RESOURCE_DATA);
		temp = inb((pnp_rd_port << 2) | 0x3);
		if (buffer != NULL)
			buffer[i] = temp;
		count++;
	}
	return (count);
}