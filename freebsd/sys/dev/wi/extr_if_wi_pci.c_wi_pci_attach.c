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
typedef  int u_int16_t ;
struct wi_softc {scalar_t__ wi_bus_type; int /*<<< orphan*/ * mem; void* wi_bmemhandle; void* wi_bmemtag; int /*<<< orphan*/  mem_rid; int /*<<< orphan*/ * local; int /*<<< orphan*/  local_rid; void* wi_localhandle; void* wi_localtag; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int CSM_READ_1 (struct wi_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CSM_WRITE_1 (struct wi_softc*,int /*<<< orphan*/ ,int) ; 
 int CSR_READ_2 (struct wi_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CSR_WRITE_2 (struct wi_softc*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  DELAY (int) ; 
 int ENXIO ; 
 int /*<<< orphan*/  RF_ACTIVE ; 
 int /*<<< orphan*/  SYS_RES_IOPORT ; 
 int /*<<< orphan*/  SYS_RES_MEMORY ; 
 scalar_t__ WI_BUS_PCI_NATIVE ; 
 int WI_CMD_BUSY ; 
 int /*<<< orphan*/  WI_COMMAND ; 
 int /*<<< orphan*/  WI_COR_OFFSET ; 
 int WI_COR_VALUE ; 
 int /*<<< orphan*/  WI_EVENT_ACK ; 
 int /*<<< orphan*/  WI_HFA384X_SWSUPPORT0_OFF ; 
 int /*<<< orphan*/  WI_INT_EN ; 
 int /*<<< orphan*/  WI_LOCAL_INTCSR ; 
 int /*<<< orphan*/  WI_LOCAL_INTEN ; 
 int /*<<< orphan*/  WI_PCICOR_OFF ; 
 int WI_PCICOR_RESET ; 
 int /*<<< orphan*/  WI_PCI_IORES ; 
 int /*<<< orphan*/  WI_PCI_LMEMRES ; 
 int /*<<< orphan*/  WI_PCI_LOCALRES ; 
 int /*<<< orphan*/  WI_PCI_MEMRES ; 
 int WI_PRISM2STA_MAGIC ; 
 void* bus_alloc_resource_any (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_release_resource (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bus_space_read_4 (void*,void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_space_write_4 (void*,void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct wi_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,...) ; 
 void* rman_get_bushandle (int /*<<< orphan*/ *) ; 
 void* rman_get_bustag (int /*<<< orphan*/ *) ; 
 int wi_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int wi_attach (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wi_free (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
wi_pci_attach(device_t dev)
{
	struct wi_softc		*sc;
	u_int32_t		command;
	u_int16_t		reg;
	int			error;
	int			timeout;

	sc = device_get_softc(dev);

	if (sc->wi_bus_type != WI_BUS_PCI_NATIVE) {
		error = wi_alloc(dev, WI_PCI_IORES);
		if (error)
			return (error);

		/* Make sure interrupts are disabled. */
		CSR_WRITE_2(sc, WI_INT_EN, 0);
		CSR_WRITE_2(sc, WI_EVENT_ACK, 0xFFFF);

		/* We have to do a magic PLX poke to enable interrupts */
		sc->local_rid = WI_PCI_LOCALRES;
		sc->local = bus_alloc_resource_any(dev, SYS_RES_IOPORT,
		    &sc->local_rid, RF_ACTIVE);
		sc->wi_localtag = rman_get_bustag(sc->local);
		sc->wi_localhandle = rman_get_bushandle(sc->local);
		command = bus_space_read_4(sc->wi_localtag, sc->wi_localhandle,
		    WI_LOCAL_INTCSR);
		command |= WI_LOCAL_INTEN;
		bus_space_write_4(sc->wi_localtag, sc->wi_localhandle,
		    WI_LOCAL_INTCSR, command);
		bus_release_resource(dev, SYS_RES_IOPORT, sc->local_rid,
		    sc->local);
		sc->local = NULL;

		sc->mem_rid = WI_PCI_MEMRES;
		sc->mem = bus_alloc_resource_any(dev, SYS_RES_MEMORY,
					&sc->mem_rid, RF_ACTIVE);
		if (sc->mem == NULL) {
			device_printf(dev, "couldn't allocate memory\n");
			wi_free(dev);
			return (ENXIO);
		}
		sc->wi_bmemtag = rman_get_bustag(sc->mem);
		sc->wi_bmemhandle = rman_get_bushandle(sc->mem);

		/*
		 * Write COR to enable PC card
		 * This is a subset of the protocol that the pccard bus code
		 * would do.  In theory, we should parse the CIS to find the
		 * COR offset.  In practice, the COR_OFFSET is always 0x3e0.
		 */
		CSM_WRITE_1(sc, WI_COR_OFFSET, WI_COR_VALUE); 
		reg = CSM_READ_1(sc, WI_COR_OFFSET);
		if (reg != WI_COR_VALUE) {
			device_printf(dev, "CSM_READ_1(WI_COR_OFFSET) "
			    "wanted %d, got %d\n", WI_COR_VALUE, reg);
			wi_free(dev);
			return (ENXIO);
		}
	} else {
		error = wi_alloc(dev, WI_PCI_LMEMRES);
		if (error)
			return (error);

		CSR_WRITE_2(sc, WI_PCICOR_OFF, WI_PCICOR_RESET);
		DELAY(250000);

		CSR_WRITE_2(sc, WI_PCICOR_OFF, 0x0000);
		DELAY(500000);

		timeout=2000000;
		while ((--timeout > 0) &&
		    (CSR_READ_2(sc, WI_COMMAND) & WI_CMD_BUSY))
			DELAY(10);

		if (timeout == 0) {
			device_printf(dev, "couldn't reset prism pci core.\n");
			wi_free(dev);
			return(ENXIO);
		}
	}

	CSR_WRITE_2(sc, WI_HFA384X_SWSUPPORT0_OFF, WI_PRISM2STA_MAGIC);
	reg = CSR_READ_2(sc, WI_HFA384X_SWSUPPORT0_OFF);
	if (reg != WI_PRISM2STA_MAGIC) {
		device_printf(dev,
		    "CSR_READ_2(WI_HFA384X_SWSUPPORT0_OFF) "
		    "wanted %d, got %d\n", WI_PRISM2STA_MAGIC, reg);
		wi_free(dev);
		return (ENXIO);
	}

	error = wi_attach(dev);
	if (error != 0)
		wi_free(dev);
	return (error);
}