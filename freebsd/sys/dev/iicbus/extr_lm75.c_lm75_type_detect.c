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
typedef  int uint32_t ;
struct lm75_softc {int sc_conf; int /*<<< orphan*/  sc_hwtype; int /*<<< orphan*/  sc_addr; int /*<<< orphan*/  sc_dev; } ;
typedef  int /*<<< orphan*/  buf8 ;

/* Variables and functions */
 int /*<<< orphan*/  HWTYPE_LM75A ; 
 int LM75_TEST_PATTERN ; 
 scalar_t__ lm75_conf_read (struct lm75_softc*) ; 
 scalar_t__ lm75_conf_write (struct lm75_softc*) ; 
 scalar_t__ lm75_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int*,int) ; 

__attribute__((used)) static int
lm75_type_detect(struct lm75_softc *sc)
{
	int i, lm75a;
	uint8_t buf8;
	uint32_t conf;

	/* Save the contents of the configuration register. */
	if (lm75_conf_read(sc) != 0)
		return (-1);
	conf = sc->sc_conf;

	/*
	 * Just write some pattern at configuration register so we can later
	 * verify.  The test pattern should be pretty harmless.
	 */
	sc->sc_conf = LM75_TEST_PATTERN;
	if (lm75_conf_write(sc) != 0)
		return (-1);

	/*
	 * Read the configuration register again and check for our test
	 * pattern.
	 */
	if (lm75_conf_read(sc) != 0)
		return (-1);
	if (sc->sc_conf != LM75_TEST_PATTERN)
		return (-1);

	/*
	 * Read from nonexistent registers (0x4 ~ 0x6).
	 * LM75A always return 0xff for nonexistent registers.
	 * LM75 will return the last read value - our test pattern written to
	 * configuration register.
	 */
	lm75a = 0;
	for (i = 4; i <= 6; i++) {
		if (lm75_read(sc->sc_dev, sc->sc_addr, i,
		    &buf8, sizeof(buf8)) < 0)
			return (-1);
		if (buf8 != LM75_TEST_PATTERN && buf8 != 0xff)
			return (-1);
		if (buf8 == 0xff)
			lm75a++;
	}
	if (lm75a == 3)
		sc->sc_hwtype = HWTYPE_LM75A;

	/* Restore the configuration register. */
	sc->sc_conf = conf;
	if (lm75_conf_write(sc) != 0)
		return (-1);

	return (0);
}