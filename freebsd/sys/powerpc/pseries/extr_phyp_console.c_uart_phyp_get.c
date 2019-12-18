#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/ * str; int /*<<< orphan*/ * u64; } ;
struct uart_phyp_softc {size_t inbuflen; scalar_t__ protocol; int /*<<< orphan*/  sc_mtx; TYPE_1__ phyp_inbuf; int /*<<< orphan*/  vtermid; } ;

/* Variables and functions */
 scalar_t__ HVTERMPROT ; 
 int /*<<< orphan*/  H_GET_TERM_CHAR ; 
 int H_SUCCESS ; 
 int /*<<< orphan*/  memcpy (void*,int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  memmove (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int phyp_pft_hcall (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,size_t*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  uart_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  uart_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
uart_phyp_get(struct uart_phyp_softc *sc, void *buffer, size_t bufsize)
{
	int err;
	int hdr = 0;

	uart_lock(&sc->sc_mtx);
	if (sc->inbuflen == 0) {
		err = phyp_pft_hcall(H_GET_TERM_CHAR, sc->vtermid,
		    0, 0, 0, &sc->inbuflen, &sc->phyp_inbuf.u64[0],
		    &sc->phyp_inbuf.u64[1]);
		if (err != H_SUCCESS) {
			uart_unlock(&sc->sc_mtx);
			return (-1);
		}
		hdr = 1; 
	}

	if (sc->inbuflen == 0) {
		uart_unlock(&sc->sc_mtx);
		return (0);
	}

	if (bufsize > sc->inbuflen)
		bufsize = sc->inbuflen;

	if ((sc->protocol == HVTERMPROT) && (hdr == 1)) {
		sc->inbuflen = sc->inbuflen - 4;
		/* The VTERM protocol has a 4 byte header, skip it here. */
		memmove(&sc->phyp_inbuf.str[0], &sc->phyp_inbuf.str[4],
		    sc->inbuflen);
	}

	memcpy(buffer, sc->phyp_inbuf.str, bufsize);
	sc->inbuflen -= bufsize;
	if (sc->inbuflen > 0)
		memmove(&sc->phyp_inbuf.str[0], &sc->phyp_inbuf.str[bufsize],
		    sc->inbuflen);

	uart_unlock(&sc->sc_mtx);
	return (bufsize);
}