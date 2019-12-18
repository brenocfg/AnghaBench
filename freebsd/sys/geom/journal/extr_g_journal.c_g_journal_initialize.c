#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  jj_offset; } ;
struct TYPE_4__ {int /*<<< orphan*/  jj_offset; } ;
struct g_journal_softc {int /*<<< orphan*/  sc_jstart; TYPE_1__ sc_active; TYPE_2__ sc_inactive; int /*<<< orphan*/  sc_journal_offset; void* sc_journal_id; void* sc_journal_previous_id; void* sc_journal_next_id; } ;

/* Variables and functions */
 void* arc4random () ; 
 int /*<<< orphan*/  g_journal_write_header (struct g_journal_softc*) ; 

__attribute__((used)) static void
g_journal_initialize(struct g_journal_softc *sc)
{

	sc->sc_journal_id = arc4random();
	sc->sc_journal_next_id = arc4random();
	sc->sc_journal_previous_id = sc->sc_journal_id;
	sc->sc_journal_offset = sc->sc_jstart;
	sc->sc_inactive.jj_offset = sc->sc_jstart;
	g_journal_write_header(sc);
	sc->sc_active.jj_offset = sc->sc_jstart;
}