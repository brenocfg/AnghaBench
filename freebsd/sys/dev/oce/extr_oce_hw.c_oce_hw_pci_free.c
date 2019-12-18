#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct resource {int dummy; } ;
typedef  void* bus_space_tag_t ;
typedef  void* bus_space_handle_t ;
struct TYPE_4__ {int flags; void* db_vhandle; void* db_bhandle; void* db_btag; struct resource* db_res; int /*<<< orphan*/  dev; void* csr_vhandle; void* csr_bhandle; void* csr_btag; struct resource* csr_res; void* devcfg_vhandle; void* devcfg_bhandle; void* devcfg_btag; struct resource* devcfg_res; } ;
typedef  TYPE_1__* POCE_SOFTC ;

/* Variables and functions */
 scalar_t__ IS_BE (TYPE_1__*) ; 
 int OCE_DEV_BE2_CFG_BAR ; 
 int OCE_DEV_CFG_BAR ; 
 int OCE_FLAGS_BE2 ; 
 int OCE_PCI_CSR_BAR ; 
 int OCE_PCI_DB_BAR ; 
 int /*<<< orphan*/  PCIR_BAR (int) ; 
 int /*<<< orphan*/  SYS_RES_MEMORY ; 
 int /*<<< orphan*/  bus_release_resource (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct resource*) ; 

void
oce_hw_pci_free(POCE_SOFTC sc)
{
	int pci_cfg_barnum = 0;

	if (IS_BE(sc) && (sc->flags & OCE_FLAGS_BE2))
		pci_cfg_barnum = OCE_DEV_BE2_CFG_BAR;
	else
		pci_cfg_barnum = OCE_DEV_CFG_BAR;

	if (sc->devcfg_res != NULL) {
		bus_release_resource(sc->dev,
				     SYS_RES_MEMORY,
				     PCIR_BAR(pci_cfg_barnum), sc->devcfg_res);
		sc->devcfg_res = (struct resource *)NULL;
		sc->devcfg_btag = (bus_space_tag_t) 0;
		sc->devcfg_bhandle = (bus_space_handle_t)0;
		sc->devcfg_vhandle = (void *)NULL;
	}

	if (sc->csr_res != NULL) {
		bus_release_resource(sc->dev,
				     SYS_RES_MEMORY,
				     PCIR_BAR(OCE_PCI_CSR_BAR), sc->csr_res);
		sc->csr_res = (struct resource *)NULL;
		sc->csr_btag = (bus_space_tag_t)0;
		sc->csr_bhandle = (bus_space_handle_t)0;
		sc->csr_vhandle = (void *)NULL;
	}

	if (sc->db_res != NULL) {
		bus_release_resource(sc->dev,
				     SYS_RES_MEMORY,
				     PCIR_BAR(OCE_PCI_DB_BAR), sc->db_res);
		sc->db_res = (struct resource *)NULL;
		sc->db_btag = (bus_space_tag_t)0;
		sc->db_bhandle = (bus_space_handle_t)0;
		sc->db_vhandle = (void *)NULL;
	}
}