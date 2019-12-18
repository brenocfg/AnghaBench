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
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_3__ {int /*<<< orphan*/  is_dtcmp; int /*<<< orphan*/  is_dva; int /*<<< orphan*/  is_dqueue; int /*<<< orphan*/  is_ddram; int /*<<< orphan*/  is_dtag; int /*<<< orphan*/  is_iommu; int /*<<< orphan*/  is_bushandle; int /*<<< orphan*/  is_bustag; } ;
struct TYPE_4__ {TYPE_1__ sis_is; } ;
struct schizo_softc {TYPE_2__ sc_is; int /*<<< orphan*/  sc_dev; int /*<<< orphan*/ * sc_mem_res; } ;
struct iommu_state {int dummy; } ;

/* Variables and functions */
 size_t STX_PCI ; 
 int /*<<< orphan*/  STX_PCI_IOMMU ; 
 int /*<<< orphan*/  STX_PCI_IOMMU_QUEUE_DIAG ; 
 int /*<<< orphan*/  STX_PCI_IOMMU_SVADIAG ; 
 int /*<<< orphan*/  STX_PCI_IOMMU_TLB_CMP_DIAG ; 
 int /*<<< orphan*/  STX_PCI_IOMMU_TLB_DATA_DIAG ; 
 int /*<<< orphan*/  STX_PCI_IOMMU_TLB_TAG_DIAG ; 
 int /*<<< orphan*/  device_get_nameunit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iommu_init (int /*<<< orphan*/ ,struct iommu_state*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rman_get_bushandle (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rman_get_bustag (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
schizo_iommu_init(struct schizo_softc *sc, int tsbsize, uint32_t dvmabase)
{

	/* Punch in our copies. */
	sc->sc_is.sis_is.is_bustag = rman_get_bustag(sc->sc_mem_res[STX_PCI]);
	sc->sc_is.sis_is.is_bushandle =
	    rman_get_bushandle(sc->sc_mem_res[STX_PCI]);
	sc->sc_is.sis_is.is_iommu = STX_PCI_IOMMU;
	sc->sc_is.sis_is.is_dtag = STX_PCI_IOMMU_TLB_TAG_DIAG;
	sc->sc_is.sis_is.is_ddram = STX_PCI_IOMMU_TLB_DATA_DIAG;
	sc->sc_is.sis_is.is_dqueue = STX_PCI_IOMMU_QUEUE_DIAG;
	sc->sc_is.sis_is.is_dva = STX_PCI_IOMMU_SVADIAG;
	sc->sc_is.sis_is.is_dtcmp = STX_PCI_IOMMU_TLB_CMP_DIAG;

	iommu_init(device_get_nameunit(sc->sc_dev),
	    (struct iommu_state *)&sc->sc_is, tsbsize, dvmabase, 0);
}