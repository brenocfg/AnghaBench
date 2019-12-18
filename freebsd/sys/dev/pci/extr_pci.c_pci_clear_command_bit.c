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
 int /*<<< orphan*/  PCIR_COMMAND ; 
 int /*<<< orphan*/  PCI_READ_CONFIG (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  PCI_WRITE_CONFIG (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static __inline void
pci_clear_command_bit(device_t dev, device_t child, uint16_t bit)
{
	uint16_t	command;

	command = PCI_READ_CONFIG(dev, child, PCIR_COMMAND, 2);
	command &= ~bit;
	PCI_WRITE_CONFIG(dev, child, PCIR_COMMAND, command, 2);
}