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
struct bgx {scalar_t__ lmac_count; size_t bgx_id; int /*<<< orphan*/  reg_base; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  M_BGX ; 
 int /*<<< orphan*/  SYS_RES_MEMORY ; 
 int /*<<< orphan*/  bgx_lmac_disable (struct bgx*,scalar_t__) ; 
 int /*<<< orphan*/ ** bgx_vnic ; 
 int /*<<< orphan*/  bus_release_resource (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct lmac* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (struct bgx*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_disable_busmaster (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rman_get_rid (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
thunder_bgx_detach(device_t dev)
{
	struct lmac *lmac;
	struct bgx *bgx;
	uint8_t lmacid;

	lmac = device_get_softc(dev);
	bgx = lmac->bgx;
	/* Disable all LMACs */
	for (lmacid = 0; lmacid < bgx->lmac_count; lmacid++)
		bgx_lmac_disable(bgx, lmacid);

	bgx_vnic[bgx->bgx_id] = NULL;
	bus_release_resource(dev, SYS_RES_MEMORY,
	    rman_get_rid(bgx->reg_base), bgx->reg_base);
	free(bgx, M_BGX);
	pci_disable_busmaster(dev);

	return (0);
}