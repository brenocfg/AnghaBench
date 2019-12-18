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
typedef  int /*<<< orphan*/  u_int32_t ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  AGP_ALI_ATTBASE ; 
 int AGP_ALI_TABLE_SIZE ; 
 int /*<<< orphan*/ * agp_ali_table ; 
 int pci_read_config (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static u_int32_t
agp_ali_get_aperture(device_t dev)
{
	/*
	 * The aperture size is derived from the low bits of attbase.
	 * I'm not sure this is correct..
	 */
	int i = pci_read_config(dev, AGP_ALI_ATTBASE, 4) & 0xf;
	if (i >= AGP_ALI_TABLE_SIZE)
		return 0;
	return agp_ali_table[i];
}