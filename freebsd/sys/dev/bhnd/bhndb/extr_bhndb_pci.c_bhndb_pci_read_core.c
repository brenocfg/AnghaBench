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
typedef  int /*<<< orphan*/  uintmax_t ;
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int u_int ;
struct resource {int dummy; } ;
struct bhndb_pci_softc {int dummy; } ;
typedef  scalar_t__ bus_size_t ;

/* Variables and functions */
 int bhndb_pci_get_core_regs (struct bhndb_pci_softc*,scalar_t__,int,struct resource**,scalar_t__*) ; 
 int /*<<< orphan*/  bus_read_1 (struct resource*,scalar_t__) ; 
 int /*<<< orphan*/  bus_read_2 (struct resource*,scalar_t__) ; 
 int /*<<< orphan*/  bus_read_4 (struct resource*,scalar_t__) ; 
 int /*<<< orphan*/  panic (char*,int,...) ; 

__attribute__((used)) static uint32_t
bhndb_pci_read_core(struct bhndb_pci_softc *sc, bus_size_t offset, u_int width)
{
	struct resource	*r;
	bus_size_t	 r_offset;
	int		 error;

	error = bhndb_pci_get_core_regs(sc, offset, width, &r, &r_offset);
	if (error) {
		panic("no PCI register window mapping %#jx+%#x: %d",
		    (uintmax_t)offset, width, error);
	}

	switch (width) {
	case 1:
		return (bus_read_1(r, r_offset));
	case 2:
		return (bus_read_2(r, r_offset));
	case 4:
		return (bus_read_4(r, r_offset));
	default:
		panic("invalid width: %u", width);
	}
}