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
struct sis_softc {int dummy; } ;
typedef  int /*<<< orphan*/ * device_t ;
typedef  int /*<<< orphan*/ * caddr_t ;
typedef  int /*<<< orphan*/  bus_space_tag_t ;

/* Variables and functions */
 int /*<<< orphan*/  X86_BUS_SPACE_IO ; 
 int /*<<< orphan*/  bus_space_read_1 (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  bus_space_write_1 (int /*<<< orphan*/ ,int,int,int) ; 
 int pci_read_config (int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  pci_write_config (int /*<<< orphan*/ *,int,int,int) ; 
 int /*<<< orphan*/ * sis_find_bridge (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
sis_read_cmos(struct sis_softc *sc, device_t dev, caddr_t dest, int off, int cnt)
{
	device_t		bridge;
	uint8_t			reg;
	int			i;
	bus_space_tag_t		btag;

	bridge = sis_find_bridge(dev);
	if (bridge == NULL)
		return;
	reg = pci_read_config(bridge, 0x48, 1);
	pci_write_config(bridge, 0x48, reg|0x40, 1);

	/* XXX */
#if defined(__amd64__) || defined(__i386__)
	btag = X86_BUS_SPACE_IO;
#endif

	for (i = 0; i < cnt; i++) {
		bus_space_write_1(btag, 0x0, 0x70, i + off);
		*(dest + i) = bus_space_read_1(btag, 0x0, 0x71);
	}

	pci_write_config(bridge, 0x48, reg & ~0x40, 1);
}