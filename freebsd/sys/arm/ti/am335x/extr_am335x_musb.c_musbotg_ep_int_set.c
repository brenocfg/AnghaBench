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
struct musbotg_super_softc {int dummy; } ;
struct musbotg_softc {struct musbotg_super_softc* sc_platform_data; } ;

/* Variables and functions */
 int IRQ_STAT0_RXSHIFT ; 
 int IRQ_STAT0_TXSHIFT ; 
 int /*<<< orphan*/  USBCTRL_INTEN_CLR0 ; 
 int /*<<< orphan*/  USBCTRL_INTEN_SET0 ; 
 int /*<<< orphan*/  USBCTRL_WRITE4 (struct musbotg_super_softc*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
musbotg_ep_int_set(struct musbotg_softc *sc, int ep, int on)
{
	struct musbotg_super_softc *ssc = sc->sc_platform_data;
	uint32_t epmask;

	epmask = ((1 << ep) << IRQ_STAT0_RXSHIFT);
	epmask |= ((1 << ep) << IRQ_STAT0_TXSHIFT);
	if (on)
		USBCTRL_WRITE4(ssc, USBCTRL_INTEN_SET0, epmask);
	else
		USBCTRL_WRITE4(ssc, USBCTRL_INTEN_CLR0, epmask);
}