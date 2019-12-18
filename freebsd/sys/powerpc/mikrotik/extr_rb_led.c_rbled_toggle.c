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
struct rbled_softc {int /*<<< orphan*/  sc_ledpin; int /*<<< orphan*/  sc_gpio; } ;

/* Variables and functions */
 int /*<<< orphan*/  GPIO_PIN_SET (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
rbled_toggle(void *priv, int onoff)
{
	struct rbled_softc *sc = priv;

	GPIO_PIN_SET(sc->sc_gpio, sc->sc_ledpin, onoff);
}