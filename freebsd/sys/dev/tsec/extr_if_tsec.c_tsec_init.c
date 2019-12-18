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
struct tsec_softc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  TSEC_GLOBAL_LOCK (struct tsec_softc*) ; 
 int /*<<< orphan*/  TSEC_GLOBAL_UNLOCK (struct tsec_softc*) ; 
 int /*<<< orphan*/  tsec_init_locked (struct tsec_softc*) ; 

__attribute__((used)) static void
tsec_init(void *xsc)
{
	struct tsec_softc *sc = xsc;

	TSEC_GLOBAL_LOCK(sc);
	tsec_init_locked(sc);
	TSEC_GLOBAL_UNLOCK(sc);
}