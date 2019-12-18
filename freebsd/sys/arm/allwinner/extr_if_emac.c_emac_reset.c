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
struct emac_softc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DELAY (int) ; 
 int /*<<< orphan*/  EMAC_CTL ; 
 int /*<<< orphan*/  EMAC_WRITE_REG (struct emac_softc*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
emac_reset(struct emac_softc *sc)
{

	EMAC_WRITE_REG(sc, EMAC_CTL, 0);
	DELAY(200);
	EMAC_WRITE_REG(sc, EMAC_CTL, 1);
	DELAY(200);
}