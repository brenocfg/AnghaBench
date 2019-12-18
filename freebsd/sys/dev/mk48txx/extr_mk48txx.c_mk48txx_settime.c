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
typedef  int /*<<< orphan*/  uint8_t ;
struct timespec {int tv_nsec; int /*<<< orphan*/  tv_sec; } ;
struct mk48txx_softc {int sc_year0; int sc_flag; int /*<<< orphan*/  sc_mtx; int /*<<< orphan*/  (* sc_nvwr ) (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* sc_nvrd ) (int /*<<< orphan*/ ,scalar_t__) ;scalar_t__ sc_clkoffset; } ;
struct clocktime {int sec; int min; int hour; int dow; int day; int mon; int year; } ;
typedef  int /*<<< orphan*/  device_t ;
typedef  scalar_t__ bus_size_t ;

/* Variables and functions */
 int /*<<< orphan*/  MK48TXX_CSR_WRITE ; 
 int /*<<< orphan*/  MK48TXX_DAY_MASK ; 
 int /*<<< orphan*/  MK48TXX_HOUR_MASK ; 
 scalar_t__ MK48TXX_ICSR ; 
 int /*<<< orphan*/  MK48TXX_IDAY ; 
 int /*<<< orphan*/  MK48TXX_IHOUR ; 
 int /*<<< orphan*/  MK48TXX_IMIN ; 
 int /*<<< orphan*/  MK48TXX_IMON ; 
 int /*<<< orphan*/  MK48TXX_ISEC ; 
 int /*<<< orphan*/  MK48TXX_IWDAY ; 
 int /*<<< orphan*/  MK48TXX_IYEAR ; 
 int /*<<< orphan*/  MK48TXX_MIN_MASK ; 
 int /*<<< orphan*/  MK48TXX_MON_MASK ; 
 int MK48TXX_NO_CENT_ADJUST ; 
 int /*<<< orphan*/  MK48TXX_SEC_MASK ; 
 int /*<<< orphan*/  MK48TXX_WDAY_CB ; 
 int MK48TXX_WDAY_CB_SHIFT ; 
 int /*<<< orphan*/  MK48TXX_WDAY_MASK ; 
 int /*<<< orphan*/  MK48TXX_YEAR_MASK ; 
 int TOBCD (int) ; 
 int /*<<< orphan*/  TOREG (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  clock_ts_to_ct (struct timespec*,struct clocktime*) ; 
 struct mk48txx_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub3 (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  stub4 (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 

int
mk48txx_settime(device_t dev, struct timespec *ts)
{
	struct mk48txx_softc *sc;
	bus_size_t clkoff;
	struct clocktime ct;
	uint8_t csr;
	int cent, year;

	sc = device_get_softc(dev);
	clkoff = sc->sc_clkoffset;

	/* Accuracy is only one second. */
	if (ts->tv_nsec >= 500000000)
		ts->tv_sec++;
	ts->tv_nsec = 0;
	clock_ts_to_ct(ts, &ct);

	mtx_lock(&sc->sc_mtx);
	/* enable write */
	csr = (*sc->sc_nvrd)(dev, clkoff + MK48TXX_ICSR);
	csr |= MK48TXX_CSR_WRITE;
	(*sc->sc_nvwr)(dev, clkoff + MK48TXX_ICSR, csr);

#define	TOREG(reg, mask, val)						\
	((*sc->sc_nvwr)(dev, clkoff + (reg),				\
	((*sc->sc_nvrd)(dev, clkoff + (reg)) & ~(mask)) |		\
	((val) & (mask))))

	TOREG(MK48TXX_ISEC, MK48TXX_SEC_MASK, TOBCD(ct.sec));
	TOREG(MK48TXX_IMIN, MK48TXX_MIN_MASK, TOBCD(ct.min));
	TOREG(MK48TXX_IHOUR, MK48TXX_HOUR_MASK, TOBCD(ct.hour));
	/* Map dow from 0 - 6 to 1 - 7; TOBCD() isn't necessary here. */
	TOREG(MK48TXX_IWDAY, MK48TXX_WDAY_MASK, ct.dow + 1);
	TOREG(MK48TXX_IDAY, MK48TXX_DAY_MASK, TOBCD(ct.day));
	TOREG(MK48TXX_IMON, MK48TXX_MON_MASK, TOBCD(ct.mon));

	year = ct.year - sc->sc_year0;
	if (sc->sc_flag & MK48TXX_NO_CENT_ADJUST) {
		cent = year / 100;
		TOREG(MK48TXX_IWDAY, MK48TXX_WDAY_CB,
		    cent << MK48TXX_WDAY_CB_SHIFT);
		year -= cent * 100;
	} else if (year > 99)
		year -= 100;
	TOREG(MK48TXX_IYEAR, MK48TXX_YEAR_MASK, TOBCD(year));

#undef TOREG

	/* load them up */
	csr = (*sc->sc_nvrd)(dev, clkoff + MK48TXX_ICSR);
	csr &= ~MK48TXX_CSR_WRITE;
	(*sc->sc_nvwr)(dev, clkoff + MK48TXX_ICSR, csr);
	mtx_unlock(&sc->sc_mtx);
	return (0);
}