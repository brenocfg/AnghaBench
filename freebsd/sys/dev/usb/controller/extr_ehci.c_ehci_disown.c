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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int uint32_t ;
typedef  int /*<<< orphan*/  uint16_t ;
typedef  int /*<<< orphan*/  ehci_softc_t ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINTF (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int EHCI_PORTSC (int /*<<< orphan*/ ) ; 
 int EHCI_PS_CLEAR ; 
 int EHCI_PS_PO ; 
 int EOREAD4 (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  EOWRITE4 (int /*<<< orphan*/ *,int,int) ; 

__attribute__((used)) static void
ehci_disown(ehci_softc_t *sc, uint16_t index, uint8_t lowspeed)
{
	uint32_t port;
	uint32_t v;

	DPRINTF("index=%d lowspeed=%d\n", index, lowspeed);

	port = EHCI_PORTSC(index);
	v = EOREAD4(sc, port) & ~EHCI_PS_CLEAR;
	EOWRITE4(sc, port, v | EHCI_PS_PO);
}