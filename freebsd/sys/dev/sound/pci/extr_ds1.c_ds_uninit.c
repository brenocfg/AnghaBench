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
struct sc_info {int /*<<< orphan*/  map; int /*<<< orphan*/  regbase; int /*<<< orphan*/  control_dmat; } ;

/* Variables and functions */
 int /*<<< orphan*/  YDSXGR_EFFCTRLBASE ; 
 int /*<<< orphan*/  YDSXGR_GLOBALCTRL ; 
 int /*<<< orphan*/  YDSXGR_MAPOFEFFECT ; 
 int /*<<< orphan*/  YDSXGR_MAPOFREC ; 
 int /*<<< orphan*/  YDSXGR_MODE ; 
 int /*<<< orphan*/  YDSXGR_NATIVEADCINVOL ; 
 int /*<<< orphan*/  YDSXGR_NATIVEDACINVOL ; 
 int /*<<< orphan*/  YDSXGR_NATIVEDACOUTVOL ; 
 int /*<<< orphan*/  YDSXGR_PLAYCTRLBASE ; 
 int /*<<< orphan*/  YDSXGR_RECCTRLBASE ; 
 int /*<<< orphan*/  bus_dmamap_unload (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_dmamem_free (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ds_enadsp (struct sc_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ds_wr (struct sc_info*,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static int
ds_uninit(struct sc_info *sc)
{
	ds_wr(sc, YDSXGR_NATIVEDACOUTVOL, 0x00000000, 4);
	ds_wr(sc, YDSXGR_NATIVEADCINVOL, 0, 4);
	ds_wr(sc, YDSXGR_NATIVEDACINVOL, 0, 4);
	ds_enadsp(sc, 0);
	ds_wr(sc, YDSXGR_MODE, 0x00010000, 4);
	ds_wr(sc, YDSXGR_MAPOFREC, 0x00000000, 4);
	ds_wr(sc, YDSXGR_MAPOFEFFECT, 0x00000000, 4);
	ds_wr(sc, YDSXGR_PLAYCTRLBASE, 0x00000000, 4);
	ds_wr(sc, YDSXGR_RECCTRLBASE, 0x00000000, 4);
	ds_wr(sc, YDSXGR_EFFCTRLBASE, 0x00000000, 4);
	ds_wr(sc, YDSXGR_GLOBALCTRL, 0, 2);

	bus_dmamap_unload(sc->control_dmat, sc->map);
	bus_dmamem_free(sc->control_dmat, sc->regbase, sc->map);

	return 0;
}