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
typedef  int /*<<< orphan*/  uint16_t ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  PCIM_CMD_MEMEN ; 
 int /*<<< orphan*/  PCIM_CMD_PORTEN ; 
#define  SYS_RES_IOPORT 129 
#define  SYS_RES_MEMORY 128 
 int /*<<< orphan*/  pci_set_command_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int
pci_enable_io_method(device_t dev, device_t child, int space)
{
	uint16_t bit;

	switch(space) {
	case SYS_RES_IOPORT:
		bit = PCIM_CMD_PORTEN;
		break;
	case SYS_RES_MEMORY:
		bit = PCIM_CMD_MEMEN;
		break;
	default:
		return (EINVAL);
	}
	pci_set_command_bit(dev, child, bit);
	return (0);
}