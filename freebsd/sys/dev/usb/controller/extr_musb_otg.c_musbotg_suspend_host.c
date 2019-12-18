#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_2__ {int status_suspend; } ;
struct musbotg_softc {TYPE_1__ sc_flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  MUSB2_MASK_SUSPMODE ; 
 int /*<<< orphan*/  MUSB2_READ_1 (struct musbotg_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MUSB2_REG_POWER ; 
 int /*<<< orphan*/  MUSB2_WRITE_1 (struct musbotg_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
musbotg_suspend_host(struct musbotg_softc *sc)
{
	uint8_t temp;

	if (sc->sc_flags.status_suspend) {
		return;
	}

	temp = MUSB2_READ_1(sc, MUSB2_REG_POWER);
	temp |= MUSB2_MASK_SUSPMODE;
	MUSB2_WRITE_1(sc, MUSB2_REG_POWER, temp);
	sc->sc_flags.status_suspend = 1;
}