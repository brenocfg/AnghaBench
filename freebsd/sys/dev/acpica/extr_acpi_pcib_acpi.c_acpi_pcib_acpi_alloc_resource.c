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
typedef  int /*<<< orphan*/  u_int ;
struct resource {int dummy; } ;
struct acpi_hpcib_softc {int /*<<< orphan*/  ap_host_res; int /*<<< orphan*/  ap_segment; } ;
typedef  int rman_res_t ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int PCI_RES_BUS ; 
 struct resource* bus_generic_alloc_resource (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int*,int,int,int,int /*<<< orphan*/ ) ; 
 struct acpi_hpcib_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int hostb_alloc_start (int,int,int,int) ; 
 struct resource* pci_domain_alloc_bus (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int,int,int,int /*<<< orphan*/ ) ; 
 struct resource* pcib_host_res_alloc (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int*,int,int,int,int /*<<< orphan*/ ) ; 

struct resource *
acpi_pcib_acpi_alloc_resource(device_t dev, device_t child, int type, int *rid,
    rman_res_t start, rman_res_t end, rman_res_t count, u_int flags)
{
#ifdef NEW_PCIB
    struct acpi_hpcib_softc *sc;
    struct resource *res;
#endif

#if defined(__i386__) || defined(__amd64__)
    start = hostb_alloc_start(type, start, end, count);
#endif

#ifdef NEW_PCIB
    sc = device_get_softc(dev);
#ifdef PCI_RES_BUS
    if (type == PCI_RES_BUS)
	return (pci_domain_alloc_bus(sc->ap_segment, child, rid, start, end,
	    count, flags));
#endif
    res = pcib_host_res_alloc(&sc->ap_host_res, child, type, rid, start, end,
	count, flags);

    /*
     * XXX: If this is a request for a specific range, assume it is
     * correct and pass it up to the parent.  What we probably want to
     * do long-term is explicitly trust any firmware-configured
     * resources during the initial bus scan on boot and then disable
     * this after that.
     */
    if (res == NULL && start + count - 1 == end)
	res = bus_generic_alloc_resource(dev, child, type, rid, start, end,
	    count, flags);
    return (res);
#else
    return (bus_generic_alloc_resource(dev, child, type, rid, start, end,
	count, flags));
#endif
}