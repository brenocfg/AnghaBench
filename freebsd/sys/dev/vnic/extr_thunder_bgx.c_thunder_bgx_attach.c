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
typedef  scalar_t__ uint8_t ;
struct lmac {struct bgx* bgx; } ;
struct bgx {int bgx_id; scalar_t__ lmac_count; int /*<<< orphan*/ * reg_base; int /*<<< orphan*/  dev; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int BGX_NODE_ID_MASK ; 
 int BGX_NODE_ID_SHIFT ; 
 int ENXIO ; 
 int MAX_BGX_PER_CN88XX ; 
 int /*<<< orphan*/  M_BGX ; 
 int M_WAITOK ; 
 int M_ZERO ; 
 int PCIR_BAR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PCI_CFG_REG_BAR_NUM ; 
 int /*<<< orphan*/  RF_ACTIVE ; 
 int /*<<< orphan*/  SYS_RES_MEMORY ; 
 int /*<<< orphan*/  bgx_get_qlm_mode (struct bgx*) ; 
 int /*<<< orphan*/  bgx_init_hw (struct bgx*) ; 
 int bgx_init_phy (struct bgx*) ; 
 int bgx_lmac_enable (struct bgx*,scalar_t__) ; 
 struct bgx** bgx_vnic ; 
 int /*<<< orphan*/ * bus_alloc_resource_any (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_release_resource (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct lmac* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  free (struct bgx*,int /*<<< orphan*/ ) ; 
 struct bgx* malloc (int,int /*<<< orphan*/ ,int) ; 
 int nic_get_node_id (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pci_disable_busmaster (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_enable_busmaster (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rman_get_rid (int /*<<< orphan*/ *) ; 
 int rman_get_start (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
thunder_bgx_attach(device_t dev)
{
	struct bgx *bgx;
	uint8_t lmacid;
	int err;
	int rid;
	struct lmac *lmac;

	bgx = malloc(sizeof(*bgx), M_BGX, (M_WAITOK | M_ZERO));
	bgx->dev = dev;

	lmac = device_get_softc(dev);
	lmac->bgx = bgx;
	/* Enable bus mastering */
	pci_enable_busmaster(dev);
	/* Allocate resources - configuration registers */
	rid = PCIR_BAR(PCI_CFG_REG_BAR_NUM);
	bgx->reg_base = bus_alloc_resource_any(dev, SYS_RES_MEMORY, &rid,
	    RF_ACTIVE);
	if (bgx->reg_base == NULL) {
		device_printf(dev, "Could not allocate CSR memory space\n");
		err = ENXIO;
		goto err_disable_device;
	}

	bgx->bgx_id = (rman_get_start(bgx->reg_base) >> BGX_NODE_ID_SHIFT) &
	    BGX_NODE_ID_MASK;
	bgx->bgx_id += nic_get_node_id(bgx->reg_base) * MAX_BGX_PER_CN88XX;

	bgx_vnic[bgx->bgx_id] = bgx;
	bgx_get_qlm_mode(bgx);

	err = bgx_init_phy(bgx);
	if (err != 0)
		goto err_free_res;

	bgx_init_hw(bgx);

	/* Enable all LMACs */
	for (lmacid = 0; lmacid < bgx->lmac_count; lmacid++) {
		err = bgx_lmac_enable(bgx, lmacid);
		if (err) {
			device_printf(dev, "BGX%d failed to enable lmac%d\n",
				bgx->bgx_id, lmacid);
			goto err_free_res;
		}
	}

	return (0);

err_free_res:
	bgx_vnic[bgx->bgx_id] = NULL;
	bus_release_resource(dev, SYS_RES_MEMORY,
	    rman_get_rid(bgx->reg_base), bgx->reg_base);
err_disable_device:
	free(bgx, M_BGX);
	pci_disable_busmaster(dev);

	return (err);
}