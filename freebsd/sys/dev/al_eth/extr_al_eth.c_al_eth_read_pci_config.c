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
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  pci_read_config (int /*<<< orphan*/ ,int,int) ; 

int
al_eth_read_pci_config(void *handle, int where, uint32_t *val)
{

	/* handle is a pci_dev */
	*val = pci_read_config((device_t)handle, where, sizeof(*val));
	return (0);
}