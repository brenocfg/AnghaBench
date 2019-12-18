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
struct xdmatest_softc {int done; int /*<<< orphan*/  mtx; } ;

/* Variables and functions */
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wakeup (struct xdmatest_softc*) ; 

__attribute__((used)) static int
xdmatest_intr(void *arg)
{
	struct xdmatest_softc *sc;

	sc = arg;

	sc->done = 1;

	mtx_lock(&sc->mtx);
	wakeup(sc);
	mtx_unlock(&sc->mtx);

	return (0);
}