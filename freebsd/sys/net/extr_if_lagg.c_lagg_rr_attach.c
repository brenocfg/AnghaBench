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
struct lagg_softc {int /*<<< orphan*/  sc_bkt; int /*<<< orphan*/  sc_bkt_count; scalar_t__ sc_seq; } ;

/* Variables and functions */

__attribute__((used)) static void
lagg_rr_attach(struct lagg_softc *sc)
{
	sc->sc_seq = 0;
	sc->sc_bkt_count = sc->sc_bkt;
}