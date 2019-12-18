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
typedef  int /*<<< orphan*/  driver_t ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 scalar_t__ bootverbose ; 
 int pnp_isolation_protocol (int /*<<< orphan*/ ) ; 
 int pnp_rd_port ; 
 int /*<<< orphan*/  printf (char*,...) ; 

__attribute__((used)) static void
pnp_identify(driver_t *driver, device_t parent)
{
	int num_pnp_devs;

	/* Try various READ_DATA ports from 0x203-0x3ff */
	for (pnp_rd_port = 0x80; (pnp_rd_port < 0xff); pnp_rd_port += 0x10) {
		if (bootverbose)
			printf("pnp_identify: Trying Read_Port at %x\n",
			    (pnp_rd_port << 2) | 0x3);

		num_pnp_devs = pnp_isolation_protocol(parent);
		if (num_pnp_devs)
			break;
	}
	if (bootverbose)
		printf("PNP Identify complete\n");
}