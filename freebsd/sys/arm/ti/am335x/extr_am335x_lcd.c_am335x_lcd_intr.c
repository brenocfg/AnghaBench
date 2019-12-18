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
typedef  int uint32_t ;
struct am335x_lcd_softc {int sc_fb_phys; int sc_fb_size; } ;

/* Variables and functions */
 int IRQ_ACB ; 
 int IRQ_EOF0 ; 
 int IRQ_EOF1 ; 
 int IRQ_FUF ; 
 int IRQ_PL ; 
 int IRQ_SYNC_LOST ; 
 int /*<<< orphan*/  LCD_END_OF_INT_IND ; 
 int /*<<< orphan*/  LCD_IRQSTATUS ; 
 int /*<<< orphan*/  LCD_LCDDMA_FB0_BASE ; 
 int /*<<< orphan*/  LCD_LCDDMA_FB0_CEILING ; 
 int /*<<< orphan*/  LCD_LCDDMA_FB1_BASE ; 
 int /*<<< orphan*/  LCD_LCDDMA_FB1_CEILING ; 
 int /*<<< orphan*/  LCD_RASTER_CTRL ; 
 int LCD_READ4 (struct am335x_lcd_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LCD_WRITE4 (struct am335x_lcd_softc*,int /*<<< orphan*/ ,int) ; 
 int RASTER_CTRL_LCDEN ; 

__attribute__((used)) static void
am335x_lcd_intr(void *arg)
{
	struct am335x_lcd_softc *sc = arg;
	uint32_t reg; 

	reg = LCD_READ4(sc, LCD_IRQSTATUS);
	LCD_WRITE4(sc, LCD_IRQSTATUS, reg);
	/* Read value back to make sure it reached the hardware */
	reg = LCD_READ4(sc, LCD_IRQSTATUS);

	if (reg & IRQ_SYNC_LOST) {
		reg = LCD_READ4(sc, LCD_RASTER_CTRL);
		reg &= ~RASTER_CTRL_LCDEN;
		LCD_WRITE4(sc, LCD_RASTER_CTRL, reg); 

		reg = LCD_READ4(sc, LCD_RASTER_CTRL);
		reg |= RASTER_CTRL_LCDEN;
		LCD_WRITE4(sc, LCD_RASTER_CTRL, reg); 
		goto done;
	}

	if (reg & IRQ_PL) {
		reg = LCD_READ4(sc, LCD_RASTER_CTRL);
		reg &= ~RASTER_CTRL_LCDEN;
		LCD_WRITE4(sc, LCD_RASTER_CTRL, reg); 

		reg = LCD_READ4(sc, LCD_RASTER_CTRL);
		reg |= RASTER_CTRL_LCDEN;
		LCD_WRITE4(sc, LCD_RASTER_CTRL, reg); 
		goto done;
	}

	if (reg & IRQ_EOF0) {
		LCD_WRITE4(sc, LCD_LCDDMA_FB0_BASE, sc->sc_fb_phys); 
		LCD_WRITE4(sc, LCD_LCDDMA_FB0_CEILING, sc->sc_fb_phys + sc->sc_fb_size - 1); 
		reg &= ~IRQ_EOF0;
	}

	if (reg & IRQ_EOF1) {
		LCD_WRITE4(sc, LCD_LCDDMA_FB1_BASE, sc->sc_fb_phys); 
		LCD_WRITE4(sc, LCD_LCDDMA_FB1_CEILING, sc->sc_fb_phys + sc->sc_fb_size - 1); 
		reg &= ~IRQ_EOF1;
	}

	if (reg & IRQ_FUF) {
		/* TODO: Handle FUF */
	}

	if (reg & IRQ_ACB) {
		/* TODO: Handle ACB */
	}

done:
	LCD_WRITE4(sc, LCD_END_OF_INT_IND, 0);
	/* Read value back to make sure it reached the hardware */
	reg = LCD_READ4(sc, LCD_END_OF_INT_IND);
}