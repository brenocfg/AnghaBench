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
struct mgb_softc {int /*<<< orphan*/  ctx; } ;

/* Variables and functions */
 int FILTER_HANDLED ; 
 int /*<<< orphan*/  iflib_admin_intr_deferred (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
mgb_legacy_intr(void *xsc)
{
	struct mgb_softc *sc;

	sc = xsc;
	iflib_admin_intr_deferred(sc->ctx);
	return (FILTER_HANDLED);
}