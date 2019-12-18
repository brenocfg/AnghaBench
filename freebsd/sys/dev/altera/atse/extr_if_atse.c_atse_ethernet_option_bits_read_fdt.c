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
struct resource {int dummy; } ;
typedef  int /*<<< orphan*/ * device_t ;

/* Variables and functions */
 int ALTERA_ETHERNET_OPTION_BITS_LEN ; 
 scalar_t__ ALTERA_ETHERNET_OPTION_BITS_OFF ; 
 int ATSE_ETHERNET_OPTION_BITS_READ ; 
 int ENOENT ; 
 int ENXIO ; 
 int RF_ACTIVE ; 
 int RF_SHAREABLE ; 
 int /*<<< orphan*/  SYS_RES_MEMORY ; 
 int /*<<< orphan*/ * atse_ethernet_option_bits ; 
 int atse_ethernet_option_bits_flag ; 
 struct resource* bus_alloc_resource_any (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int*,int) ; 
 int /*<<< orphan*/  bus_read_1 (struct resource*,scalar_t__) ; 
 int /*<<< orphan*/  bus_release_resource (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,struct resource*) ; 
 int /*<<< orphan*/ * device_find_child (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_get_parent (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
atse_ethernet_option_bits_read_fdt(device_t dev)
{
	struct resource *res;
	device_t fdev;
	int i, rid;

	if (atse_ethernet_option_bits_flag & ATSE_ETHERNET_OPTION_BITS_READ) {
		return (0);
	}

	fdev = device_find_child(device_get_parent(dev), "cfi", 0);
	if (fdev == NULL) {
		return (ENOENT);
	}

	rid = 0;
	res = bus_alloc_resource_any(fdev, SYS_RES_MEMORY, &rid,
	    RF_ACTIVE | RF_SHAREABLE);
	if (res == NULL) {
		return (ENXIO);
	}

	for (i = 0; i < ALTERA_ETHERNET_OPTION_BITS_LEN; i++) {
		atse_ethernet_option_bits[i] = bus_read_1(res,
		    ALTERA_ETHERNET_OPTION_BITS_OFF + i);
	}

	bus_release_resource(fdev, SYS_RES_MEMORY, rid, res);
	atse_ethernet_option_bits_flag |= ATSE_ETHERNET_OPTION_BITS_READ;

	return (0);
}