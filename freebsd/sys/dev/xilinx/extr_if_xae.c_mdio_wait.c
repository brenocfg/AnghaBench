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
struct xae_softc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DELAY (int) ; 
 int MDIO_CTRL_READY ; 
 int READ4 (struct xae_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XAE_MDIO_CTRL ; 
 int /*<<< orphan*/  printf (char*) ; 

__attribute__((used)) static int
mdio_wait(struct xae_softc *sc)
{
	uint32_t reg;
	int timeout;

	timeout = 200;

	do {
		reg = READ4(sc, XAE_MDIO_CTRL);
		if (reg & MDIO_CTRL_READY)
			break;
		DELAY(1);
	} while (timeout--);

	if (timeout <= 0) {
		printf("Failed to get MDIO ready\n");
		return (1);
	}

	return (0);
}