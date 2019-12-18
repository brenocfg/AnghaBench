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
typedef  int u_int ;
struct resource {int dummy; } ;
struct bhndb_pci_probe {int /*<<< orphan*/  dev; } ;
typedef  int /*<<< orphan*/  bus_size_t ;
typedef  int /*<<< orphan*/  bhnd_size_t ;
typedef  int /*<<< orphan*/  bhnd_addr_t ;

/* Variables and functions */
 int bhndb_pci_probe_map (struct bhndb_pci_probe*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,struct resource**,int /*<<< orphan*/ *) ; 
 void bus_write_1 (struct resource*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 void bus_write_2 (struct resource*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 void bus_write_4 (struct resource*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  panic (char*,int) ; 

__attribute__((used)) static void
bhndb_pci_probe_write(struct bhndb_pci_probe *probe, bhnd_addr_t addr,
    bhnd_size_t offset, uint32_t value, u_int width)
{
	struct resource	*r;
	bus_size_t	 res_offset;
	int		 error;

	/* Map the target address */
	error = bhndb_pci_probe_map(probe, addr, offset, width, &r,
	    &res_offset);
	if (error) {
		device_printf(probe->dev, "error mapping %#jx+%#jx for "
		    "writing: %d\n", addr, offset, error);
		return;
	}

	/* Perform write */
	switch (width) {
	case 1:
		return (bus_write_1(r, res_offset, value));
	case 2:
		return (bus_write_2(r, res_offset, value));
	case 4:
		return (bus_write_4(r, res_offset, value));
	default:
		panic("unsupported width: %u", width);
	}
}