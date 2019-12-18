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
struct panel_info {int ivclk; int fixvclk; int clkval_f; int v_pulse_width; int v_front_porch; int v_back_porch; int h_pulse_width; int h_front_porch; int h_back_porch; int width; int height; } ;
struct TYPE_2__ {int fb_pbase; int fb_stride; int fb_height; } ;
struct fimd_softc {TYPE_1__ sc_info; struct panel_info* panel; } ;

/* Variables and functions */
 int BPPMODE_F_OFFSET ; 
 int BPPMODE_F_RGB_16BIT_565 ; 
 int CHANNEL0_EN ; 
 int CLKVAL_F_OFFSET ; 
 int /*<<< orphan*/  DPCLKCON ; 
 int DPCLKCON_EN ; 
 int /*<<< orphan*/  DWRITE4 (struct fimd_softc*,int /*<<< orphan*/ ,int) ; 
 int ENLOCAL_F ; 
 int ENWIN_F_ENABLE ; 
 int HALF_WORD_SWAP_EN ; 
 int HOZVAL_OFFSET ; 
 int HSYNC_PULSE_WIDTH_OFFSET ; 
 int H_BACK_PORCH_OFFSET ; 
 int H_FRONT_PORCH_OFFSET ; 
 int LINEVAL_OFFSET ; 
 int OSD_RIGHTBOTX_F_OFFSET ; 
 int OSD_RIGHTBOTY_F_OFFSET ; 
 int READ4 (struct fimd_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SHADOWCON ; 
 int /*<<< orphan*/  VIDCON0 ; 
 int VIDCON0_ENVID ; 
 int VIDCON0_ENVID_F ; 
 int /*<<< orphan*/  VIDCON1 ; 
 int /*<<< orphan*/  VIDOSD0B ; 
 int /*<<< orphan*/  VIDOSD0C ; 
 int /*<<< orphan*/  VIDTCON0 ; 
 int /*<<< orphan*/  VIDTCON1 ; 
 int /*<<< orphan*/  VIDTCON2 ; 
 int /*<<< orphan*/  VIDW00ADD0B0 ; 
 int /*<<< orphan*/  VIDW00ADD1B0 ; 
 int /*<<< orphan*/  VIDW00ADD2 ; 
 int VSYNC_PULSE_WIDTH_OFFSET ; 
 int V_BACK_PORCH_OFFSET ; 
 int V_FRONT_PORCH_OFFSET ; 
 int /*<<< orphan*/  WINCON0 ; 
 int /*<<< orphan*/  WRITE4 (struct fimd_softc*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
fimd_init(struct fimd_softc *sc)
{
	struct panel_info *panel;
	int reg;

	panel = sc->panel;

	/* fb_init */
	reg = panel->ivclk | panel->fixvclk;
	DWRITE4(sc,VIDCON1,reg);

	reg = (VIDCON0_ENVID | VIDCON0_ENVID_F);
	reg |= (panel->clkval_f << CLKVAL_F_OFFSET);
	WRITE4(sc,VIDCON0,reg);

	reg = (panel->v_pulse_width << VSYNC_PULSE_WIDTH_OFFSET);
	reg |= (panel->v_front_porch << V_FRONT_PORCH_OFFSET);
	reg |= (panel->v_back_porch << V_BACK_PORCH_OFFSET);
	DWRITE4(sc,VIDTCON0,reg);

	reg = (panel->h_pulse_width << HSYNC_PULSE_WIDTH_OFFSET);
	reg |= (panel->h_front_porch << H_FRONT_PORCH_OFFSET);
	reg |= (panel->h_back_porch << H_BACK_PORCH_OFFSET);
	DWRITE4(sc,VIDTCON1,reg);

	reg = ((panel->width - 1) << HOZVAL_OFFSET);
	reg |= ((panel->height - 1) << LINEVAL_OFFSET);
	DWRITE4(sc,VIDTCON2,reg);

	reg = sc->sc_info.fb_pbase;
	WRITE4(sc, VIDW00ADD0B0, reg);
	reg += (sc->sc_info.fb_stride * (sc->sc_info.fb_height + 1));
	WRITE4(sc, VIDW00ADD1B0, reg);
	WRITE4(sc, VIDW00ADD2, sc->sc_info.fb_stride);

	reg = ((panel->width - 1) << OSD_RIGHTBOTX_F_OFFSET);
	reg |= ((panel->height - 1) << OSD_RIGHTBOTY_F_OFFSET);
	WRITE4(sc,VIDOSD0B,reg);

	reg = panel->width * panel->height;
	WRITE4(sc,VIDOSD0C,reg);

	reg = READ4(sc, SHADOWCON);
	reg |= CHANNEL0_EN;
	reg &= ~(1 << 5); /* disable local path for channel0 */
	WRITE4(sc,SHADOWCON,reg);

	reg = BPPMODE_F_RGB_16BIT_565 << BPPMODE_F_OFFSET;
	reg |= ENWIN_F_ENABLE | HALF_WORD_SWAP_EN; /* Note: swap=0 when ENLOCAL==1 */
	reg &= ~ENLOCAL_F; /* use DMA */
	WRITE4(sc,WINCON0,reg);

	/* Enable DisplayPort Clk */
	WRITE4(sc, DPCLKCON, DPCLKCON_EN);

	return (0);
}