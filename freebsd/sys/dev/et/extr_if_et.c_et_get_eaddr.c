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
typedef  int uint32_t ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int ETHER_ADDR_LEN ; 
 int /*<<< orphan*/  ET_PCIR_MAC_ADDR0 ; 
 int /*<<< orphan*/  ET_PCIR_MAC_ADDR1 ; 
 int pci_read_config (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
et_get_eaddr(device_t dev, uint8_t eaddr[])
{
	uint32_t val;
	int i;

	val = pci_read_config(dev, ET_PCIR_MAC_ADDR0, 4);
	for (i = 0; i < 4; ++i)
		eaddr[i] = (val >> (8 * i)) & 0xff;

	val = pci_read_config(dev, ET_PCIR_MAC_ADDR1, 2);
	for (; i < ETHER_ADDR_LEN; ++i)
		eaddr[i] = (val >> (8 * (i - 4))) & 0xff;
}