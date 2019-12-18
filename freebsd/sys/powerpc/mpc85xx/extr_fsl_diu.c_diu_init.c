#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct panel_info {int panel_hbp; int panel_hpw; int panel_hfp; int panel_vbp; int panel_vpw; int panel_vfp; int /*<<< orphan*/  panel_freq; } ;
struct TYPE_4__ {int fb_height; int fb_width; int fb_pbase; } ;
struct diu_softc {int /*<<< orphan*/ * res; TYPE_2__** sc_planes; TYPE_1__ sc_info; TYPE_2__* sc_cursor; TYPE_2__* sc_gamma; int /*<<< orphan*/  sc_dev; struct panel_info sc_panel; } ;
struct diu_area_descriptor {int dummy; } ;
struct TYPE_5__ {int pixel_format; scalar_t__ next_ad_addr; void* chroma_key_min; scalar_t__ chroma_key_max; scalar_t__ display_offset; scalar_t__ aoi_offset; void* aoi_size; void* source_size; void* bitmap_address; } ;

/* Variables and functions */
 int BP_H_SHIFT ; 
 int BP_V_SHIFT ; 
 int /*<<< orphan*/  BUS_SPACE_MAXADDR_32BIT ; 
 int DELTA_Y_S ; 
 int /*<<< orphan*/  DIU_BGND ; 
 int /*<<< orphan*/  DIU_CURSOR ; 
 int /*<<< orphan*/  DIU_CURS_POS ; 
 int /*<<< orphan*/  DIU_DESC_1 ; 
 int /*<<< orphan*/  DIU_DESC_2 ; 
 int /*<<< orphan*/  DIU_DESC_3 ; 
 int /*<<< orphan*/  DIU_DISP_SIZE ; 
 int /*<<< orphan*/  DIU_DIU_MODE ; 
 int /*<<< orphan*/  DIU_GAMMA ; 
 int /*<<< orphan*/  DIU_HSYN_PARA ; 
 int /*<<< orphan*/  DIU_INT_MASK ; 
 int DIU_MODE_M ; 
 int DIU_MODE_NORMAL ; 
 int DIU_MODE_S ; 
 int /*<<< orphan*/  DIU_PLUT ; 
 int /*<<< orphan*/  DIU_VSYN_PARA ; 
 int ENXIO ; 
 int FP_H_SHIFT ; 
 int FP_V_SHIFT ; 
 int MAKE_PXLFMT (int,int,int,int,int,int,int,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  M_DEVBUF ; 
 int /*<<< orphan*/  M_ZERO ; 
 int PW_H_SHIFT ; 
 int PW_V_SHIFT ; 
 int bus_read_4 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_write_4 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 TYPE_2__* contigmalloc (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 scalar_t__ diu_set_pxclk (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 void* htole32 (int) ; 
 int vtophys (TYPE_2__*) ; 

__attribute__((used)) static int
diu_init(struct diu_softc *sc)
{
	struct panel_info *panel;
	int reg;

	panel = &sc->sc_panel;

	/* Temporarily disable the DIU while configuring */
	reg = bus_read_4(sc->res[0], DIU_DIU_MODE);
	reg &= ~(DIU_MODE_M << DIU_MODE_S);
	bus_write_4(sc->res[0], DIU_DIU_MODE, reg);

	if (diu_set_pxclk(sc->sc_dev, panel->panel_freq) < 0) {
		return (ENXIO);
	}

	/* Configure DIU */
	/* Need to set these somehow later... */
	bus_write_4(sc->res[0], DIU_GAMMA, vtophys(sc->sc_gamma));
	bus_write_4(sc->res[0], DIU_CURSOR, vtophys(sc->sc_cursor));
	bus_write_4(sc->res[0], DIU_CURS_POS, 0);

	reg = ((sc->sc_info.fb_height) << DELTA_Y_S);
	reg |= sc->sc_info.fb_width;
	bus_write_4(sc->res[0], DIU_DISP_SIZE, reg);

	reg = (panel->panel_hbp << BP_H_SHIFT);
	reg |= (panel->panel_hpw << PW_H_SHIFT);
	reg |= (panel->panel_hfp << FP_H_SHIFT);
	bus_write_4(sc->res[0], DIU_HSYN_PARA, reg);

	reg = (panel->panel_vbp << BP_V_SHIFT);
	reg |= (panel->panel_vpw << PW_V_SHIFT);
	reg |= (panel->panel_vfp << FP_V_SHIFT);
	bus_write_4(sc->res[0], DIU_VSYN_PARA, reg);

	bus_write_4(sc->res[0], DIU_BGND, 0);

	/* Mask all the interrupts */
	bus_write_4(sc->res[0], DIU_INT_MASK, 0x3f);

	/* Reset all layers */
	sc->sc_planes[0] = contigmalloc(sizeof(struct diu_area_descriptor),
		M_DEVBUF, M_ZERO, 0, BUS_SPACE_MAXADDR_32BIT, 32, 0);
	bus_write_4(sc->res[0], DIU_DESC_1, vtophys(sc->sc_planes[0]));
	bus_write_4(sc->res[0], DIU_DESC_2, 0);
	bus_write_4(sc->res[0], DIU_DESC_3, 0);

	/* Setup first plane */
	/* Area descriptor fields are little endian, so byte swap. */
	/* Word 0: Pixel format */
	/* Set to 8:8:8:8 ARGB, 4 bytes per pixel, no flip. */
#define MAKE_PXLFMT(as,rs,gs,bs,a,r,g,b,f,s)	\
		htole32((as << (4 * a)) | (rs << 4 * r) | \
		    (gs << 4 * g) | (bs << 4 * b) | \
		    (f << 28) | (s << 16) | \
		    (a << 25) | (r << 19) | \
		    (g << 21) | (b << 24))
	reg = MAKE_PXLFMT(8, 8, 8, 8, 3, 2, 1, 0, 1, 3);
	sc->sc_planes[0]->pixel_format = reg;
	/* Word 1: Bitmap address */
	sc->sc_planes[0]->bitmap_address = htole32(sc->sc_info.fb_pbase);
	/* Word 2: Source size/global alpha */
	reg = (sc->sc_info.fb_width | (sc->sc_info.fb_height << 12));
	sc->sc_planes[0]->source_size = htole32(reg);
	/* Word 3: AOI Size */
	reg = (sc->sc_info.fb_width | (sc->sc_info.fb_height << 16));
	sc->sc_planes[0]->aoi_size = htole32(reg);
	/* Word 4: AOI Offset */
	sc->sc_planes[0]->aoi_offset = 0;
	/* Word 5: Display offset */
	sc->sc_planes[0]->display_offset = 0;
	/* Word 6: Chroma key max */
	sc->sc_planes[0]->chroma_key_max = 0;
	/* Word 7: Chroma key min */
	reg = 255 << 16 | 255 << 8 | 255;
	sc->sc_planes[0]->chroma_key_min = htole32(reg);
	/* Word 8: Next AD */
	sc->sc_planes[0]->next_ad_addr = 0;

	/* TODO: derive this from the panel size */
	bus_write_4(sc->res[0], DIU_PLUT, 0x1f5f666);

	/* Enable DIU in normal mode */
	reg = bus_read_4(sc->res[0], DIU_DIU_MODE);
	reg &= ~(DIU_MODE_M << DIU_MODE_S);
	reg |= (DIU_MODE_NORMAL << DIU_MODE_S);
	bus_write_4(sc->res[0], DIU_DIU_MODE, reg);

	return (0);
}