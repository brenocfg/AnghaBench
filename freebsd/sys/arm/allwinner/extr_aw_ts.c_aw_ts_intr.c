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
struct aw_ts_softc {int temp_data; int temp_step; int temp_offset; } ;

/* Variables and functions */
 int READ (struct aw_ts_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TEMP_DATA ; 
 int /*<<< orphan*/  TP_FIFOS ; 
 int TP_FIFOS_TEMP_IRQ_PENDING ; 
 int /*<<< orphan*/  WRITE (struct aw_ts_softc*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
aw_ts_intr(void *arg)
{
	struct aw_ts_softc *sc;
	int val;

	sc= (struct aw_ts_softc *)arg;

	val = READ(sc, TP_FIFOS);
	if (val & TP_FIFOS_TEMP_IRQ_PENDING) {
		/* Convert the value to millicelsius then millikelvin */
		sc->temp_data = (READ(sc, TEMP_DATA) * sc->temp_step - sc->temp_offset)
			+ 273150;
	}

	WRITE(sc, TP_FIFOS, val);
}