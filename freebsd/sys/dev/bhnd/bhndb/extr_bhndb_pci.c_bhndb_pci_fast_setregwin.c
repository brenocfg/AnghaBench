#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  cfg_offset; } ;
struct TYPE_4__ {TYPE_1__ dyn; } ;
struct bhndb_regwin {int win_type; scalar_t__ win_size; TYPE_2__ d; } ;
typedef  int /*<<< orphan*/  device_t ;
typedef  scalar_t__ bhnd_addr_t ;

/* Variables and functions */
#define  BHNDB_REGWIN_T_DYN 128 
 int EINVAL ; 
 int ENODEV ; 
 int ERANGE ; 
 scalar_t__ UINT32_MAX ; 
 int /*<<< orphan*/  pci_write_config (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int) ; 

__attribute__((used)) static int
bhndb_pci_fast_setregwin(device_t dev, device_t pci_dev,
    const struct bhndb_regwin *rw, bhnd_addr_t addr)
{
	/* The PCI bridge core only supports 32-bit addressing, regardless
	 * of the bus' support for 64-bit addressing */
	if (addr > UINT32_MAX)
		return (ERANGE);

	switch (rw->win_type) {
	case BHNDB_REGWIN_T_DYN:
		/* Addresses must be page aligned */
		if (addr % rw->win_size != 0)
			return (EINVAL);

		pci_write_config(pci_dev, rw->d.dyn.cfg_offset, addr, 4);
		break;
	default:
		return (ENODEV);
	}

	return (0);
}