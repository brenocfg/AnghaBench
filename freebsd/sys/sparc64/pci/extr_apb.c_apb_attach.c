#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct sysctl_oid {int dummy; } ;
struct sysctl_ctx_list {int dummy; } ;
struct TYPE_4__ {void* sub; void* sec; } ;
struct TYPE_5__ {TYPE_1__ bus; void* domain; void* pribus; void* bridgectl; } ;
struct TYPE_6__ {TYPE_2__ ops_pcib_sc; } ;
struct apb_softc {void* sc_memmap; void* sc_iomap; TYPE_3__ sc_bsc; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  APBR_IOMAP ; 
 int /*<<< orphan*/  APBR_MEMMAP ; 
 int /*<<< orphan*/  APB_IO_SCALE ; 
 int /*<<< orphan*/  APB_MEM_SCALE ; 
 int /*<<< orphan*/  CTLFLAG_RD ; 
 int /*<<< orphan*/  OID_AUTO ; 
 int /*<<< orphan*/  PCIR_BRIDGECTL_1 ; 
 int /*<<< orphan*/  PCIR_PRIBUS_1 ; 
 int /*<<< orphan*/  PCIR_SECBUS_1 ; 
 int /*<<< orphan*/  PCIR_SUBBUS_1 ; 
 int /*<<< orphan*/  SYSCTL_ADD_UINT (struct sysctl_ctx_list*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,void**,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  SYSCTL_CHILDREN (struct sysctl_oid*) ; 
 int /*<<< orphan*/  apb_map_print (void*,int /*<<< orphan*/ ) ; 
 scalar_t__ bootverbose ; 
 int bus_generic_attach (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_add_child (int /*<<< orphan*/ ,char*,int) ; 
 struct apb_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 struct sysctl_ctx_list* device_get_sysctl_ctx (int /*<<< orphan*/ ) ; 
 struct sysctl_oid* device_get_sysctl_tree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  ofw_pcib_gen_setup (int /*<<< orphan*/ ) ; 
 void* pci_get_bus (int /*<<< orphan*/ ) ; 
 void* pci_get_domain (int /*<<< orphan*/ ) ; 
 void* pci_read_config (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pci_write_config (int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*,int) ; 
 int /*<<< orphan*/  printf (char*) ; 

__attribute__((used)) static int
apb_attach(device_t dev)
{
	struct apb_softc *sc;
	struct sysctl_ctx_list *sctx;
	struct sysctl_oid *soid;

	sc = device_get_softc(dev);

	/*
	 * Get current bridge configuration.
	 */
	sc->sc_bsc.ops_pcib_sc.domain = pci_get_domain(dev);
	sc->sc_bsc.ops_pcib_sc.pribus = pci_get_bus(dev);
	pci_write_config(dev, PCIR_PRIBUS_1, sc->sc_bsc.ops_pcib_sc.pribus, 1);
	sc->sc_bsc.ops_pcib_sc.bus.sec =
	    pci_read_config(dev, PCIR_SECBUS_1, 1);
	sc->sc_bsc.ops_pcib_sc.bus.sub =
	    pci_read_config(dev, PCIR_SUBBUS_1, 1);
	sc->sc_bsc.ops_pcib_sc.bridgectl =
	    pci_read_config(dev, PCIR_BRIDGECTL_1, 2);
	sc->sc_iomap = pci_read_config(dev, APBR_IOMAP, 1);
	sc->sc_memmap = pci_read_config(dev, APBR_MEMMAP, 1);

	/*
	 * Setup SYSCTL reporting nodes.
	 */
	sctx = device_get_sysctl_ctx(dev);
	soid = device_get_sysctl_tree(dev);
	SYSCTL_ADD_UINT(sctx, SYSCTL_CHILDREN(soid), OID_AUTO, "domain",
	    CTLFLAG_RD, &sc->sc_bsc.ops_pcib_sc.domain, 0,
	    "Domain number");
	SYSCTL_ADD_UINT(sctx, SYSCTL_CHILDREN(soid), OID_AUTO, "pribus",
	    CTLFLAG_RD, &sc->sc_bsc.ops_pcib_sc.pribus, 0,
	    "Primary bus number");
	SYSCTL_ADD_UINT(sctx, SYSCTL_CHILDREN(soid), OID_AUTO, "secbus",
	    CTLFLAG_RD, &sc->sc_bsc.ops_pcib_sc.bus.sec, 0,
	    "Secondary bus number");
	SYSCTL_ADD_UINT(sctx, SYSCTL_CHILDREN(soid), OID_AUTO, "subbus",
	    CTLFLAG_RD, &sc->sc_bsc.ops_pcib_sc.bus.sub, 0,
	    "Subordinate bus number");

	ofw_pcib_gen_setup(dev);

	if (bootverbose) {
		device_printf(dev, "  domain            %d\n",
		    sc->sc_bsc.ops_pcib_sc.domain);
		device_printf(dev, "  secondary bus     %d\n",
		    sc->sc_bsc.ops_pcib_sc.bus.sec);
		device_printf(dev, "  subordinate bus   %d\n",
		    sc->sc_bsc.ops_pcib_sc.bus.sub);
		device_printf(dev, "  I/O decode        ");
		apb_map_print(sc->sc_iomap, APB_IO_SCALE);
		printf("\n");
		device_printf(dev, "  memory decode     ");
		apb_map_print(sc->sc_memmap, APB_MEM_SCALE);
		printf("\n");
	}

	device_add_child(dev, "pci", -1);
	return (bus_generic_attach(dev));
}