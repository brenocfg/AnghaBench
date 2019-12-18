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
typedef  int uint8_t ;
struct lm75_softc {int /*<<< orphan*/  sc_addr; int /*<<< orphan*/  sc_dev; scalar_t__ sc_conf; } ;
typedef  int /*<<< orphan*/  buf8 ;

/* Variables and functions */
 int LM75_CONF ; 
 int LM75_CONF_MASK ; 
 scalar_t__ lm75_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int) ; 

__attribute__((used)) static int
lm75_conf_write(struct lm75_softc *sc)
{
	uint8_t buf8[2];

	buf8[0] = LM75_CONF;
	buf8[1] = (uint8_t)sc->sc_conf & LM75_CONF_MASK;
	if (lm75_write(sc->sc_dev, sc->sc_addr, buf8, sizeof(buf8)) < 0)
		return (-1);

	return (0);
}