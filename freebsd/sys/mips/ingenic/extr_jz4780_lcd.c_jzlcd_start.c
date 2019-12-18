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
struct jzlcd_softc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  LCDCTRL ; 
 int /*<<< orphan*/  LCDCTRL_DIS ; 
 int /*<<< orphan*/  LCDCTRL_ENA ; 
 int /*<<< orphan*/  LCDOSDS ; 
 int /*<<< orphan*/  LCDSTATE ; 
 int /*<<< orphan*/  LCD_READ (struct jzlcd_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LCD_WRITE (struct jzlcd_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
jzlcd_start(struct jzlcd_softc *sc)
{
	uint32_t ctrl;

	/* Clear status registers */
	LCD_WRITE(sc, LCDSTATE, 0);
	LCD_WRITE(sc, LCDOSDS, 0);
	/* Enable the controller */
	ctrl = LCD_READ(sc, LCDCTRL);
	ctrl |= LCDCTRL_ENA;
	ctrl &= ~LCDCTRL_DIS;
	LCD_WRITE(sc, LCDCTRL, ctrl);
}