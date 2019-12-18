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
struct thunder_pem_softc {int /*<<< orphan*/  id; } ;
struct rman {int dummy; } ;
struct resource {int dummy; } ;
typedef  int /*<<< orphan*/  rman_res_t ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int EINVAL ; 
 int PCI_RES_BUS ; 
 int bus_generic_adjust_resource (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,struct resource*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct thunder_pem_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int pci_domain_adjust_bus (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct resource*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int rman_adjust_resource (struct resource*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rman_is_region_manager (struct resource*,struct rman*) ; 
 struct rman* thunder_pem_rman (struct thunder_pem_softc*,int) ; 

__attribute__((used)) static int
thunder_pem_adjust_resource(device_t dev, device_t child, int type,
    struct resource *res, rman_res_t start, rman_res_t end)
{
	struct thunder_pem_softc *sc;
	struct rman *rm;

	sc = device_get_softc(dev);
#if defined(NEW_PCIB) && defined(PCI_RES_BUS)
	if (type == PCI_RES_BUS)
		return (pci_domain_adjust_bus(sc->id, child, res, start, end));
#endif

	rm = thunder_pem_rman(sc, type);
	if (rm == NULL)
		return (bus_generic_adjust_resource(dev, child, type, res,
		    start, end));
	if (!rman_is_region_manager(res, rm))
		/*
		 * This means a child device has a memory or I/O
		 * resource not from you which shouldn't happen.
		 */
		return (EINVAL);
	return (rman_adjust_resource(res, start, end));
}