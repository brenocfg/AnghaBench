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
typedef  int /*<<< orphan*/  uint32_t ;
struct psycho_softc {int /*<<< orphan*/  sc_dev; int /*<<< orphan*/  sc_mem_res; struct iommu_state* sc_is; } ;
struct iommu_state {int /*<<< orphan*/  is_dtcmp; int /*<<< orphan*/  is_dva; int /*<<< orphan*/  is_dqueue; int /*<<< orphan*/  is_ddram; int /*<<< orphan*/  is_dtag; int /*<<< orphan*/  is_iommu; int /*<<< orphan*/  is_bushandle; int /*<<< orphan*/  is_bustag; } ;

/* Variables and functions */
 int /*<<< orphan*/  PSR_IOMMU ; 
 int /*<<< orphan*/  PSR_IOMMU_QUEUE_DIAG ; 
 int /*<<< orphan*/  PSR_IOMMU_SVADIAG ; 
 int /*<<< orphan*/  PSR_IOMMU_TLB_CMP_DIAG ; 
 int /*<<< orphan*/  PSR_IOMMU_TLB_DATA_DIAG ; 
 int /*<<< orphan*/  PSR_IOMMU_TLB_TAG_DIAG ; 
 int /*<<< orphan*/  device_get_nameunit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iommu_init (int /*<<< orphan*/ ,struct iommu_state*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rman_get_bushandle (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rman_get_bustag (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
psycho_iommu_init(struct psycho_softc *sc, int tsbsize, uint32_t dvmabase)
{
	struct iommu_state *is = sc->sc_is;

	/* Punch in our copies. */
	is->is_bustag = rman_get_bustag(sc->sc_mem_res);
	is->is_bushandle = rman_get_bushandle(sc->sc_mem_res);
	is->is_iommu = PSR_IOMMU;
	is->is_dtag = PSR_IOMMU_TLB_TAG_DIAG;
	is->is_ddram = PSR_IOMMU_TLB_DATA_DIAG;
	is->is_dqueue = PSR_IOMMU_QUEUE_DIAG;
	is->is_dva = PSR_IOMMU_SVADIAG;
	is->is_dtcmp = PSR_IOMMU_TLB_CMP_DIAG;

	iommu_init(device_get_nameunit(sc->sc_dev), is, tsbsize, dvmabase, 0);
}