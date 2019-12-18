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
struct timespec {int dummy; } ;
struct mk48txx_softc {int sc_flag; int /*<<< orphan*/  sc_mtx; int /*<<< orphan*/  (* sc_nvwr ) (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* sc_nvrd ) (int /*<<< orphan*/ ,scalar_t__) ;scalar_t__ sc_year0; scalar_t__ sc_clkoffset; } ;
struct clocktime {int dow; int year; void* mon; void* day; void* hour; void* min; void* sec; scalar_t__ nsec; } ;
typedef  int /*<<< orphan*/  device_t ;
typedef  scalar_t__ bus_size_t ;

/* Variables and functions */
 void* FROMBCD (int) ; 
 int FROMREG (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MK48TXX_CSR_READ ; 
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
 int POSIX_BASE_YEAR ; 
 int clock_ct_to_ts (struct clocktime*,struct timespec*) ; 
 struct mk48txx_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub3 (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  stub4 (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 

int
mk48txx_gettime(device_t dev, struct timespec *ts)
{
	struct mk48txx_softc *sc;
	bus_size_t clkoff;
	struct clocktime ct;
	int year;
	uint8_t csr;

	sc = device_get_softc(dev);
	clkoff = sc->sc_clkoffset;

	mtx_lock(&sc->sc_mtx);
	/* enable read (stop time) */
	csr = (*sc->sc_nvrd)(dev, clkoff + MK48TXX_ICSR);
	csr |= MK48TXX_CSR_READ;
	(*sc->sc_nvwr)(dev, clkoff + MK48TXX_ICSR, csr);

#define	FROMREG(reg, mask)	((*sc->sc_nvrd)(dev, clkoff + (reg)) & (mask))

	ct.nsec = 0;
	ct.sec = FROMBCD(FROMREG(MK48TXX_ISEC, MK48TXX_SEC_MASK));
	ct.min = FROMBCD(FROMREG(MK48TXX_IMIN, MK48TXX_MIN_MASK));
	ct.hour = FROMBCD(FROMREG(MK48TXX_IHOUR, MK48TXX_HOUR_MASK));
	ct.day = FROMBCD(FROMREG(MK48TXX_IDAY, MK48TXX_DAY_MASK));
#if 0
	/* Map dow from 1 - 7 to 0 - 6; FROMBCD() isn't necessary here. */
	ct.dow = FROMREG(MK48TXX_IWDAY, MK48TXX_WDAY_MASK) - 1;
#else
	/*
	 * Set dow = -1 because some drivers (for example the NetBSD and
	 * OpenBSD mk48txx(4)) don't set it correctly.
	 */
	ct.dow = -1;
#endif
	ct.mon = FROMBCD(FROMREG(MK48TXX_IMON, MK48TXX_MON_MASK));
	year = FROMBCD(FROMREG(MK48TXX_IYEAR, MK48TXX_YEAR_MASK));
	year += sc->sc_year0;
	if (sc->sc_flag & MK48TXX_NO_CENT_ADJUST)
		year += (FROMREG(MK48TXX_IWDAY, MK48TXX_WDAY_CB) >>
		    MK48TXX_WDAY_CB_SHIFT) * 100;
	else if (year < POSIX_BASE_YEAR)
		year += 100;

#undef FROMREG

	ct.year = year;

	/* time wears on */
	csr = (*sc->sc_nvrd)(dev, clkoff + MK48TXX_ICSR);
	csr &= ~MK48TXX_CSR_READ;
	(*sc->sc_nvwr)(dev, clkoff + MK48TXX_ICSR, csr);
	mtx_unlock(&sc->sc_mtx);

	return (clock_ct_to_ts(&ct, ts));
}