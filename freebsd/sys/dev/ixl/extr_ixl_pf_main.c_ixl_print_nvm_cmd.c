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
struct i40e_nvm_access {int command; int config; int offset; int data_size; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int I40E_NVM_READ ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,...) ; 

void
ixl_print_nvm_cmd(device_t dev, struct i40e_nvm_access *nvma)
{
	if ((nvma->command == I40E_NVM_READ) &&
	    ((nvma->config & 0xFF) == 0xF) &&
	    (((nvma->config & 0xF00) >> 8) == 0xF) &&
	    (nvma->offset == 0) &&
	    (nvma->data_size == 1)) {
		// device_printf(dev, "- Get Driver Status Command\n");
	}
	else if (nvma->command == I40E_NVM_READ) {

	}
	else {
		switch (nvma->command) {
		case 0xB:
			device_printf(dev, "- command: I40E_NVM_READ\n");
			break;
		case 0xC:
			device_printf(dev, "- command: I40E_NVM_WRITE\n");
			break;
		default:
			device_printf(dev, "- command: unknown 0x%08x\n", nvma->command);
			break;
		}

		device_printf(dev, "- config (ptr)  : 0x%02x\n", nvma->config & 0xFF);
		device_printf(dev, "- config (flags): 0x%01x\n", (nvma->config & 0xF00) >> 8);
		device_printf(dev, "- offset : 0x%08x\n", nvma->offset);
		device_printf(dev, "- data_s : 0x%08x\n", nvma->data_size);
	}
}