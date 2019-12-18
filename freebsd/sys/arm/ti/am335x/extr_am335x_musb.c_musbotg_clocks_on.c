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
struct musbotg_softc {size_t sc_id; } ;

/* Variables and functions */
 int* USB_CTRL ; 
 int /*<<< orphan*/  ti_scm_reg_read_4 (int,int*) ; 
 int /*<<< orphan*/  ti_scm_reg_write_4 (int,int) ; 

__attribute__((used)) static void
musbotg_clocks_on(void *arg)
{
	struct musbotg_softc *sc;
	uint32_t c, reg;

	sc = arg;
        reg = USB_CTRL[sc->sc_id];

	ti_scm_reg_read_4(reg, &c);
	c &= ~3; /* Enable power */
	c |= 1 << 19; /* VBUS detect enable */
	c |= 1 << 20; /* Session end enable */
	ti_scm_reg_write_4(reg, c);
}