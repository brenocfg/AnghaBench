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
struct rtwn_softc {int page_count; int pktbuf_count; } ;

/* Variables and functions */
 int r92c_llt_write (struct rtwn_softc*,int,int) ; 

int
r92c_llt_init(struct rtwn_softc *sc)
{
	int i, error;

	/* Reserve pages [0; page_count]. */
	for (i = 0; i < sc->page_count; i++) {
		if ((error = r92c_llt_write(sc, i, i + 1)) != 0)
			return (error);
	}
	/* NB: 0xff indicates end-of-list. */
	if ((error = r92c_llt_write(sc, i, 0xff)) != 0)
		return (error);
	/*
	 * Use pages [page_count + 1; pktbuf_count - 1]
	 * as ring buffer.
	 */
	for (++i; i < sc->pktbuf_count - 1; i++) {
		if ((error = r92c_llt_write(sc, i, i + 1)) != 0)
			return (error);
	}
	/* Make the last page point to the beginning of the ring buffer. */
	error = r92c_llt_write(sc, i, sc->page_count + 1);
	return (error);
}