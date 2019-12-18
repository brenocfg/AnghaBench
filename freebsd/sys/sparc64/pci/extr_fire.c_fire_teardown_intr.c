#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  size_t u_long ;
typedef  int u_int ;
struct resource {int dummy; } ;
struct fire_softc {int* sc_msi_msiq_table; size_t sc_msi_first; scalar_t__ sc_msiq_first; scalar_t__ sc_msiq_ino_first; int /*<<< orphan*/  sc_ign; } ;
typedef  int /*<<< orphan*/  device_t ;
struct TYPE_2__ {int /*<<< orphan*/ * iv_ic; } ;

/* Variables and functions */
 int FIRE_PCI_READ_8 (struct fire_softc*,scalar_t__) ; 
 int /*<<< orphan*/  FIRE_PCI_WRITE_8 (struct fire_softc*,scalar_t__,int) ; 
 scalar_t__ FO_PCI_EQ_CTRL_CLR_BASE ; 
 int FO_PCI_EQ_CTRL_CLR_COVERR ; 
 int FO_PCI_EQ_CTRL_CLR_DIS ; 
 int FO_PCI_EQ_CTRL_CLR_E2I ; 
 scalar_t__ FO_PCI_EQ_HD_BASE ; 
 int FO_PCI_EQ_HD_MASK ; 
 int FO_PCI_EQ_HD_SHFT ; 
 scalar_t__ FO_PCI_EQ_TL_BASE ; 
 int FO_PCI_EQ_TL_MASK ; 
 int FO_PCI_EQ_TL_SHFT ; 
 scalar_t__ FO_PCI_MSI_MAP_BASE ; 
 int FO_PCI_MSI_MAP_V ; 
 size_t INTMAP_VEC (int /*<<< orphan*/ ,scalar_t__) ; 
 int bus_generic_teardown_intr (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct resource*,void*) ; 
 struct fire_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fire_ic ; 
 TYPE_1__* intr_vectors ; 
 scalar_t__ rman_get_rid (struct resource*) ; 
 int rman_get_start (struct resource*) ; 
 int /*<<< orphan*/  rman_set_end (struct resource*,int) ; 
 int /*<<< orphan*/  rman_set_start (struct resource*,int) ; 

__attribute__((used)) static int
fire_teardown_intr(device_t dev, device_t child, struct resource *ires,
    void *cookie)
{
	struct fire_softc *sc;
	u_long vec;
	int error;
	u_int msi, msiq;

	sc = device_get_softc(dev);
	if (rman_get_rid(ires) != 0) {
		msi = rman_get_start(ires);
		msiq = sc->sc_msi_msiq_table[msi - sc->sc_msi_first];
		vec = INTMAP_VEC(sc->sc_ign, msiq + sc->sc_msiq_ino_first);
		msiq += sc->sc_msiq_first;
		msi <<= 3;
		FIRE_PCI_WRITE_8(sc, FO_PCI_MSI_MAP_BASE + msi,
		    FIRE_PCI_READ_8(sc, FO_PCI_MSI_MAP_BASE + msi) &
		    ~FO_PCI_MSI_MAP_V);
		msiq <<= 3;
		FIRE_PCI_WRITE_8(sc, FO_PCI_EQ_CTRL_CLR_BASE + msiq,
		    FO_PCI_EQ_CTRL_CLR_COVERR | FO_PCI_EQ_CTRL_CLR_E2I |
		    FO_PCI_EQ_CTRL_CLR_DIS);
		FIRE_PCI_WRITE_8(sc, FO_PCI_EQ_TL_BASE + msiq,
		    (0 << FO_PCI_EQ_TL_SHFT) & FO_PCI_EQ_TL_MASK);
		FIRE_PCI_WRITE_8(sc, FO_PCI_EQ_HD_BASE + msiq,
		    (0 << FO_PCI_EQ_HD_SHFT) & FO_PCI_EQ_HD_MASK);
		intr_vectors[vec].iv_ic = &fire_ic;
		/*
		 * The MD interrupt code needs the vector rather than the MSI.
		 */
		rman_set_start(ires, vec);
		rman_set_end(ires, vec);
		error = bus_generic_teardown_intr(dev, child, ires, cookie);
		msi >>= 3;
		rman_set_start(ires, msi);
		rman_set_end(ires, msi);
		return (error);
	}
	return (bus_generic_teardown_intr(dev, child, ires, cookie));
}