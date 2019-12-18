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
struct timespec {int tv_nsec; int /*<<< orphan*/  tv_sec; } ;
struct ds1553_softc {int (* sc_read ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;int /*<<< orphan*/  sc_mtx; int /*<<< orphan*/  (* sc_write ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ;scalar_t__ year_offset; } ;
struct clocktime {scalar_t__ year; scalar_t__ mon; scalar_t__ day; scalar_t__ dow; scalar_t__ hour; scalar_t__ min; scalar_t__ sec; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int DS1553_BIT_WRITE ; 
 int DS1553_MASK_DATE ; 
 int DS1553_MASK_DAYOFWEEK ; 
 int DS1553_MASK_HOUR ; 
 int DS1553_MASK_MINUTES ; 
 int DS1553_MASK_MONTH ; 
 int DS1553_MASK_SECONDS ; 
 int /*<<< orphan*/  DS1553_OFF_CONTROL ; 
 int /*<<< orphan*/  DS1553_OFF_DATE ; 
 int /*<<< orphan*/  DS1553_OFF_DAYOFWEEK ; 
 int /*<<< orphan*/  DS1553_OFF_HOURS ; 
 int /*<<< orphan*/  DS1553_OFF_MINUTES ; 
 int /*<<< orphan*/  DS1553_OFF_MONTH ; 
 int /*<<< orphan*/  DS1553_OFF_SECONDS ; 
 int /*<<< orphan*/  DS1553_OFF_YEAR ; 
 int TOBCD (scalar_t__) ; 
 int /*<<< orphan*/  bzero (struct clocktime*,int) ; 
 int /*<<< orphan*/  clock_ts_to_ct (struct timespec*,struct clocktime*) ; 
 struct ds1553_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtx_lock_spin (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock_spin (int /*<<< orphan*/ *) ; 
 int stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub10 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub3 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub4 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub5 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub6 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub7 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub8 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub9 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

int
ds1553_settime(device_t dev, struct timespec *ts)
{
	struct clocktime ct;
	struct ds1553_softc *sc;
	uint8_t control;

	sc = device_get_softc(dev);
	bzero(&ct, sizeof(struct clocktime));

	/* Accuracy is only one second. */
	if (ts->tv_nsec >= 500000000)
		ts->tv_sec++;
	ts->tv_nsec = 0;
	clock_ts_to_ct(ts, &ct);

	ct.year -= sc->year_offset;

	mtx_lock_spin(&sc->sc_mtx);

	/* Halt updates to external registers */
	control = (*sc->sc_read)(dev, DS1553_OFF_CONTROL) | DS1553_BIT_WRITE;
	(*sc->sc_write)(dev, DS1553_OFF_CONTROL, control);

	(*sc->sc_write)(dev, DS1553_OFF_SECONDS, TOBCD(ct.sec) &
	    DS1553_MASK_SECONDS);
	(*sc->sc_write)(dev, DS1553_OFF_MINUTES, TOBCD(ct.min) &
	    DS1553_MASK_MINUTES);
	(*sc->sc_write)(dev, DS1553_OFF_HOURS, TOBCD(ct.hour) &
	    DS1553_MASK_HOUR);
	(*sc->sc_write)(dev, DS1553_OFF_DAYOFWEEK, TOBCD(ct.dow + 1) &
	    DS1553_MASK_DAYOFWEEK);
	(*sc->sc_write)(dev, DS1553_OFF_DATE, TOBCD(ct.day) &
	    DS1553_MASK_DATE);
	(*sc->sc_write)(dev, DS1553_OFF_MONTH, TOBCD(ct.mon) &
	    DS1553_MASK_MONTH);
	(*sc->sc_write)(dev, DS1553_OFF_YEAR, TOBCD(ct.year));

	/* Resume updates to external registers */
	control &= ~DS1553_BIT_WRITE;
	(*sc->sc_write)(dev, DS1553_OFF_CONTROL, control);

	mtx_unlock_spin(&sc->sc_mtx);

	return (0);
}