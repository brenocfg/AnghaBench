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
typedef  scalar_t__ u_int ;
struct TYPE_3__ {int cfg_offset; } ;
struct TYPE_4__ {TYPE_1__ dyn; } ;
struct bhndb_regwin {scalar_t__ win_type; TYPE_2__ d; } ;
typedef  int /*<<< orphan*/  device_t ;
typedef  scalar_t__ bhnd_addr_t ;

/* Variables and functions */
 scalar_t__ BHNDB_PCI_BARCTRL_WRITE_RETRY ; 
 scalar_t__ BHNDB_REGWIN_T_DYN ; 
 int /*<<< orphan*/  DELAY (int) ; 
 int ENODEV ; 
 int bhndb_pci_fast_setregwin (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct bhndb_regwin const*,scalar_t__) ; 
 scalar_t__ pci_read_config (int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static int
bhndb_pci_compat_setregwin(device_t dev, device_t pci_dev,
    const struct bhndb_regwin *rw, bhnd_addr_t addr)
{
	int		error;
	int		reg;

	if (rw->win_type != BHNDB_REGWIN_T_DYN)
		return (ENODEV);

	reg = rw->d.dyn.cfg_offset;
	for (u_int i = 0; i < BHNDB_PCI_BARCTRL_WRITE_RETRY; i++) {
		if ((error = bhndb_pci_fast_setregwin(dev, pci_dev, rw, addr)))
			return (error);

		if (pci_read_config(pci_dev, reg, 4) == addr)
			return (0);

		DELAY(10);
	}

	/* Unable to set window */
	return (ENODEV);
}