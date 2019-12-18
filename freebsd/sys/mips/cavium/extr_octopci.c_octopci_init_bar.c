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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int uint64_t ;
typedef  int uint32_t ;
struct octopci_softc {unsigned int sc_io_next; unsigned int sc_mem1_next; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int CVMX_OCT_PCI_IO_BASE ; 
 unsigned int CVMX_OCT_PCI_IO_SIZE ; 
 int CVMX_OCT_PCI_MEM1_BASE ; 
 unsigned int CVMX_OCT_PCI_MEM1_SIZE ; 
 int PCIM_BAR_IO_BASE ; 
#define  PCIM_BAR_MEM_64 128 
 scalar_t__ PCIM_BAR_MEM_BASE ; 
 int PCIM_BAR_MEM_TYPE ; 
 int /*<<< orphan*/  PCIM_CMD_MEMEN ; 
 int /*<<< orphan*/  PCIM_CMD_PORTEN ; 
 scalar_t__ PCIR_BAR (unsigned int) ; 
 scalar_t__ PCIR_BIOS ; 
 scalar_t__ PCI_BAR_IO (int) ; 
 struct octopci_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,unsigned int,unsigned int,unsigned int,unsigned int) ; 
 int octopci_read_config (int /*<<< orphan*/ ,unsigned int,unsigned int,unsigned int,scalar_t__,int) ; 
 int /*<<< orphan*/  octopci_write_config (int /*<<< orphan*/ ,unsigned int,unsigned int,unsigned int,scalar_t__,int,int) ; 
 void* roundup2 (unsigned int,unsigned int) ; 

__attribute__((used)) static unsigned
octopci_init_bar(device_t dev, unsigned b, unsigned s, unsigned f, unsigned barnum, uint8_t *commandp)
{
	struct octopci_softc *sc;
	uint64_t bar;
	unsigned size;
	int barsize;

	sc = device_get_softc(dev);

	octopci_write_config(dev, b, s, f, PCIR_BAR(barnum), 0xffffffff, 4);
	bar = octopci_read_config(dev, b, s, f, PCIR_BAR(barnum), 4);

	if (bar == 0) {
		/* Bar not implemented; got to next bar.  */
		return (barnum + 1);
	}

	if (PCI_BAR_IO(bar)) {
		size = ~(bar & PCIM_BAR_IO_BASE) + 1;

		sc->sc_io_next = roundup2(sc->sc_io_next, size);
		if (sc->sc_io_next + size > CVMX_OCT_PCI_IO_SIZE) {
			device_printf(dev, "%02x.%02x:%02x: no ports for BAR%u.\n",
			    b, s, f, barnum);
			return (barnum + 1);
		}
		octopci_write_config(dev, b, s, f, PCIR_BAR(barnum),
		    CVMX_OCT_PCI_IO_BASE + sc->sc_io_next, 4);
		sc->sc_io_next += size;

		/*
		 * Enable I/O ports.
		 */
		*commandp |= PCIM_CMD_PORTEN;

		return (barnum + 1);
	} else {
		if (PCIR_BAR(barnum) == PCIR_BIOS) {
			/*
			 * ROM BAR is always 32-bit.
			 */
			barsize = 1;
		} else {
			switch (bar & PCIM_BAR_MEM_TYPE) {
			case PCIM_BAR_MEM_64:
				/*
				 * XXX
				 * High 32 bits are all zeroes for now.
				 */
				octopci_write_config(dev, b, s, f, PCIR_BAR(barnum + 1), 0, 4);
				barsize = 2;
				break;
			default:
				barsize = 1;
				break;
			}
		}

		size = ~(bar & (uint32_t)PCIM_BAR_MEM_BASE) + 1;

		sc->sc_mem1_next = roundup2(sc->sc_mem1_next, size);
		if (sc->sc_mem1_next + size > CVMX_OCT_PCI_MEM1_SIZE) {
			device_printf(dev, "%02x.%02x:%02x: no memory for BAR%u.\n",
			    b, s, f, barnum);
			return (barnum + barsize);
		}
		octopci_write_config(dev, b, s, f, PCIR_BAR(barnum),
		    CVMX_OCT_PCI_MEM1_BASE + sc->sc_mem1_next, 4);
		sc->sc_mem1_next += size;

		/*
		 * Enable memory access.
		 */
		*commandp |= PCIM_CMD_MEMEN;

		return (barnum + barsize);
	}
}