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
typedef  int /*<<< orphan*/  uint16_t ;
struct ehci_softc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  EHCI_PORTSC (int /*<<< orphan*/ ) ; 
 int EHCI_PORTSC_PSPD_MASK ; 
 int EHCI_PORTSC_PSPD_SHIFT ; 
 int EHCI_PORT_SPEED_HIGH ; 
 int EHCI_PORT_SPEED_LOW ; 
 int EOREAD4 (struct ehci_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UPS_HIGH_SPEED ; 
 int /*<<< orphan*/  UPS_LOW_SPEED ; 

uint16_t
ehci_get_port_speed_portsc(struct ehci_softc *sc, uint16_t index)
{
	uint32_t v;

	v = EOREAD4(sc, EHCI_PORTSC(index));
	v = (v >> EHCI_PORTSC_PSPD_SHIFT) & EHCI_PORTSC_PSPD_MASK;

	if (v == EHCI_PORT_SPEED_HIGH)
		return (UPS_HIGH_SPEED);
	if (v == EHCI_PORT_SPEED_LOW)
		return (UPS_LOW_SPEED);
	return (0);
}