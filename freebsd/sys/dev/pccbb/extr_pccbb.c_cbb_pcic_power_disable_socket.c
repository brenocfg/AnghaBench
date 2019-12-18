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
struct cbb_softc {int /*<<< orphan*/ * exca; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  CARD_OFF ; 
 int /*<<< orphan*/  DPRINTF (char*) ; 
 int /*<<< orphan*/  EXCA_INTR ; 
 int /*<<< orphan*/  EXCA_INTR_ENABLE ; 
 int /*<<< orphan*/  EXCA_PWRCTL ; 
 int /*<<< orphan*/  cbb_power (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct cbb_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  exca_putb (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int hz ; 
 int /*<<< orphan*/  pause (char*,int) ; 

__attribute__((used)) static int
cbb_pcic_power_disable_socket(device_t brdev, device_t child)
{
	struct cbb_softc *sc = device_get_softc(brdev);

	DPRINTF(("cbb_pcic_socket_disable\n"));

	/* Turn off the card's interrupt and leave it in reset, wait 10ms */
	exca_putb(&sc->exca[0], EXCA_INTR, 0);
	pause("cbbP1", hz / 100);

	/* power down the socket */
	cbb_power(brdev, CARD_OFF);
	exca_putb(&sc->exca[0], EXCA_PWRCTL, 0);

	/* wait 300ms until power fails (Tpf). */
	pause("cbbP2", hz * 300 / 1000);

	/* enable CSC interrupts */
	exca_putb(&sc->exca[0], EXCA_INTR, EXCA_INTR_ENABLE);
	return (0);
}