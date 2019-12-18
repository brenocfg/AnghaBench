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
typedef  scalar_t__ uint8_t ;
typedef  scalar_t__ uint32_t ;
struct lm75_softc {scalar_t__ sc_conf; int /*<<< orphan*/  sc_addr; int /*<<< orphan*/  sc_dev; } ;
typedef  int /*<<< orphan*/  buf8 ;

/* Variables and functions */
 int /*<<< orphan*/  LM75_CONF ; 
 scalar_t__ lm75_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__*,int) ; 

__attribute__((used)) static int
lm75_conf_read(struct lm75_softc *sc)
{
	uint8_t buf8;

	if (lm75_read(sc->sc_dev, sc->sc_addr, LM75_CONF,
	    &buf8, sizeof(buf8)) < 0)
		return (-1);
	sc->sc_conf = (uint32_t)buf8;

	return (0);
}