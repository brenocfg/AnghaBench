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
struct ucom_softc {int const sc_lsr; int sc_flag; } ;
struct tty {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINTFN (int,char*,struct ucom_softc*,int const) ; 
 int /*<<< orphan*/  MA_OWNED ; 
 int UCOM_FLAG_LSRTXIDLE ; 
 int /*<<< orphan*/  UCOM_MTX_ASSERT (struct ucom_softc*,int /*<<< orphan*/ ) ; 
 int ULSR_TSRE ; 
 int ULSR_TXRDY ; 
 struct ucom_softc* tty_softc (struct tty*) ; 

__attribute__((used)) static bool
ucom_busy(struct tty *tp)
{
	struct ucom_softc *sc = tty_softc(tp);
	const uint8_t txidle = ULSR_TXRDY | ULSR_TSRE;

	UCOM_MTX_ASSERT(sc, MA_OWNED);

	DPRINTFN(3, "sc = %p lsr 0x%02x\n", sc, sc->sc_lsr);

	/*
	 * If the driver maintains the txidle bits in LSR, we can use them to
	 * determine whether the transmitter is busy or idle.  Otherwise we have
	 * to assume it is idle to avoid hanging forever on tcdrain(3).
	 */
	if (sc->sc_flag & UCOM_FLAG_LSRTXIDLE)
		return ((sc->sc_lsr & txidle) != txidle);
	else
		return (false);
}