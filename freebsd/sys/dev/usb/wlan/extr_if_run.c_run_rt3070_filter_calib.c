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
struct run_softc {int dummy; } ;

/* Variables and functions */
 int ETIMEDOUT ; 
 int /*<<< orphan*/  run_bbp_read (struct run_softc*,int,int*) ; 
 int /*<<< orphan*/  run_bbp_write (struct run_softc*,int,int) ; 
 int /*<<< orphan*/  run_delay (struct run_softc*,int) ; 
 int /*<<< orphan*/  run_rt3070_rf_read (struct run_softc*,int,int*) ; 
 int /*<<< orphan*/  run_rt3070_rf_write (struct run_softc*,int,int) ; 

__attribute__((used)) static int
run_rt3070_filter_calib(struct run_softc *sc, uint8_t init, uint8_t target,
    uint8_t *val)
{
	uint8_t rf22, rf24;
	uint8_t bbp55_pb, bbp55_sb, delta;
	int ntries;

	/* program filter */
	run_rt3070_rf_read(sc, 24, &rf24);
	rf24 = (rf24 & 0xc0) | init;	/* initial filter value */
	run_rt3070_rf_write(sc, 24, rf24);

	/* enable baseband loopback mode */
	run_rt3070_rf_read(sc, 22, &rf22);
	run_rt3070_rf_write(sc, 22, rf22 | 0x01);

	/* set power and frequency of passband test tone */
	run_bbp_write(sc, 24, 0x00);
	for (ntries = 0; ntries < 100; ntries++) {
		/* transmit test tone */
		run_bbp_write(sc, 25, 0x90);
		run_delay(sc, 10);
		/* read received power */
		run_bbp_read(sc, 55, &bbp55_pb);
		if (bbp55_pb != 0)
			break;
	}
	if (ntries == 100)
		return (ETIMEDOUT);

	/* set power and frequency of stopband test tone */
	run_bbp_write(sc, 24, 0x06);
	for (ntries = 0; ntries < 100; ntries++) {
		/* transmit test tone */
		run_bbp_write(sc, 25, 0x90);
		run_delay(sc, 10);
		/* read received power */
		run_bbp_read(sc, 55, &bbp55_sb);

		delta = bbp55_pb - bbp55_sb;
		if (delta > target)
			break;

		/* reprogram filter */
		rf24++;
		run_rt3070_rf_write(sc, 24, rf24);
	}
	if (ntries < 100) {
		if (rf24 != init)
			rf24--;	/* backtrack */
		*val = rf24;
		run_rt3070_rf_write(sc, 24, rf24);
	}

	/* restore initial state */
	run_bbp_write(sc, 24, 0x00);

	/* disable baseband loopback mode */
	run_rt3070_rf_read(sc, 22, &rf22);
	run_rt3070_rf_write(sc, 22, rf22 & ~0x01);

	return (0);
}