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
struct ath_softc {TYPE_1__* sc_rxedma; int /*<<< orphan*/  sc_rxbuf; } ;
struct ath_buf {int /*<<< orphan*/ * bf_m; } ;
struct TYPE_2__ {struct ath_buf* m_holdbf; } ;

/* Variables and functions */
 size_t HAL_RX_QUEUE_HP ; 
 size_t HAL_RX_QUEUE_LP ; 
 int /*<<< orphan*/  TAILQ_INSERT_TAIL (int /*<<< orphan*/ *,struct ath_buf*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ath_rxbuf_init (struct ath_softc*,struct ath_buf*) ; 
 int /*<<< orphan*/  bf_list ; 
 int /*<<< orphan*/  m_freem (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
ath_legacy_flush_rxholdbf(struct ath_softc *sc)
{
	struct ath_buf *bf;

	/* XXX ATH_RX_LOCK_ASSERT(sc); */
	/*
	 * If there are RX holding buffers, free them here and return
	 * them to the list.
	 *
	 * XXX should just verify that bf->bf_m is NULL, as it must
	 * be at this point!
	 */
	bf = sc->sc_rxedma[HAL_RX_QUEUE_HP].m_holdbf;
	if (bf != NULL) {
		if (bf->bf_m != NULL)
			m_freem(bf->bf_m);
		bf->bf_m = NULL;
		TAILQ_INSERT_TAIL(&sc->sc_rxbuf, bf, bf_list);
		(void) ath_rxbuf_init(sc, bf);
	}
	sc->sc_rxedma[HAL_RX_QUEUE_HP].m_holdbf = NULL;

	bf = sc->sc_rxedma[HAL_RX_QUEUE_LP].m_holdbf;
	if (bf != NULL) {
		if (bf->bf_m != NULL)
			m_freem(bf->bf_m);
		bf->bf_m = NULL;
		TAILQ_INSERT_TAIL(&sc->sc_rxbuf, bf, bf_list);
		(void) ath_rxbuf_init(sc, bf);
	}
	sc->sc_rxedma[HAL_RX_QUEUE_LP].m_holdbf = NULL;

	return (0);
}