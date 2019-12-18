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
struct udl_softc {int /*<<< orphan*/  sc_cmd_buf_free; int /*<<< orphan*/  sc_mtx; int /*<<< orphan*/  sc_cv; } ;
struct udl_cmd_buf {scalar_t__ off; } ;

/* Variables and functions */
 int M_WAITOK ; 
 struct udl_cmd_buf* TAILQ_FIRST (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TAILQ_REMOVE (int /*<<< orphan*/ *,struct udl_cmd_buf*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cv_wait (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  entry ; 

__attribute__((used)) static struct udl_cmd_buf *
udl_cmd_buf_alloc_locked(struct udl_softc *sc, int flags)
{
	struct udl_cmd_buf *cb;

	while ((cb = TAILQ_FIRST(&sc->sc_cmd_buf_free)) == NULL) {
		if (flags != M_WAITOK)
			break;
		cv_wait(&sc->sc_cv, &sc->sc_mtx);
	}
	if (cb != NULL) {
		TAILQ_REMOVE(&sc->sc_cmd_buf_free, cb, entry);
		cb->off = 0;
	}
	return (cb);
}