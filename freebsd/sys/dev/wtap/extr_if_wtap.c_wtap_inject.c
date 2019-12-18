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
struct wtap_softc {int /*<<< orphan*/  sc_mtx; int /*<<< orphan*/  sc_rxtask; int /*<<< orphan*/  sc_tq; int /*<<< orphan*/  sc_rxbuf; } ;
struct wtap_buf {struct mbuf* m; } ;
struct mbuf {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  KASSERT (int /*<<< orphan*/ ,char*) ; 
 int M_NOWAIT ; 
 int /*<<< orphan*/  M_WTAP_RXBUF ; 
 int M_ZERO ; 
 int /*<<< orphan*/  STAILQ_INSERT_TAIL (int /*<<< orphan*/ *,struct wtap_buf*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bf_list ; 
 scalar_t__ malloc (int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  taskqueue_enqueue (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void
wtap_inject(struct wtap_softc *sc, struct mbuf *m)
{
      struct wtap_buf *bf = (struct wtap_buf *)malloc(sizeof(struct wtap_buf),
          M_WTAP_RXBUF, M_NOWAIT | M_ZERO);
      KASSERT(bf != NULL, ("could not allocated a new wtap_buf\n"));
      bf->m = m;

      mtx_lock(&sc->sc_mtx);
      STAILQ_INSERT_TAIL(&sc->sc_rxbuf, bf, bf_list);
      taskqueue_enqueue(sc->sc_tq, &sc->sc_rxtask);
      mtx_unlock(&sc->sc_mtx);
}