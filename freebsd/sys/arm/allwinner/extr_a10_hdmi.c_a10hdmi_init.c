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
struct a10hdmi_softc {int dummy; } ;

/* Variables and functions */
 int CTRL_MODULE_EN ; 
 int /*<<< orphan*/  DELAY (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HDMI_CTRL ; 
 int /*<<< orphan*/  HDMI_ENABLE_DELAY ; 
 int /*<<< orphan*/  HDMI_PADCTRL0 ; 
 int /*<<< orphan*/  HDMI_PADCTRL1 ; 
 int /*<<< orphan*/  HDMI_PLLDBG0 ; 
 int /*<<< orphan*/  HDMI_WRITE (struct a10hdmi_softc*,int /*<<< orphan*/ ,int) ; 
 int PADCTRL0_BIASEN ; 
 int PADCTRL0_CKEN ; 
 int PADCTRL0_LDOCEN ; 
 int PADCTRL0_LDODEN ; 
 int PADCTRL0_PWENC ; 
 int PADCTRL0_PWEND ; 
 int PADCTRL0_PWENG ; 
 int PADCTRL0_TXEN ; 
 int PADCTRL1_AMPCK_OPT ; 
 int PADCTRL1_AMP_OPT ; 
 int PADCTRL1_EMPCK_OPT ; 
 int PADCTRL1_EMP_OPT ; 
 int PADCTRL1_REG_AMP_EN ; 
 int PADCTRL1_REG_DEN ; 
 int PADCTRL1_REG_DENCK ; 
 int PADCTRL1_REG_EMP_EN ; 
 int PLLDBG0_CKIN_SEL_PLL3 ; 

__attribute__((used)) static void
a10hdmi_init(struct a10hdmi_softc *sc)
{
	/* Enable the HDMI module */
	HDMI_WRITE(sc, HDMI_CTRL, CTRL_MODULE_EN);

	/* Configure PLL/DRV settings */
	HDMI_WRITE(sc, HDMI_PADCTRL0, PADCTRL0_BIASEN | PADCTRL0_LDOCEN |
	    PADCTRL0_LDODEN | PADCTRL0_PWENC | PADCTRL0_PWEND |
	    PADCTRL0_PWENG | PADCTRL0_CKEN | PADCTRL0_TXEN);
	HDMI_WRITE(sc, HDMI_PADCTRL1, PADCTRL1_AMP_OPT | PADCTRL1_AMPCK_OPT |
	    PADCTRL1_EMP_OPT | PADCTRL1_EMPCK_OPT | PADCTRL1_REG_DEN |
	    PADCTRL1_REG_DENCK | PADCTRL1_REG_EMP_EN | PADCTRL1_REG_AMP_EN);

	/* Select PLL3 as input clock */
	HDMI_WRITE(sc, HDMI_PLLDBG0, PLLDBG0_CKIN_SEL_PLL3);

	DELAY(HDMI_ENABLE_DELAY);
}