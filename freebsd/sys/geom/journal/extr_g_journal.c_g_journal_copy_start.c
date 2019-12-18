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
struct g_journal_softc {int sc_journal_copying; } ;

/* Variables and functions */
 int /*<<< orphan*/  GJ_DEBUG (int,char*) ; 
 int /*<<< orphan*/  g_journal_copy_send (struct g_journal_softc*) ; 
 int /*<<< orphan*/  g_journal_metadata_update (struct g_journal_softc*) ; 

__attribute__((used)) static void
g_journal_copy_start(struct g_journal_softc *sc)
{

	/*
	 * Remember in metadata that we're starting to copy journaled data
	 * to the data provider.
	 * In case of power failure, we will copy these data once again on boot.
	 */
	if (!sc->sc_journal_copying) {
		sc->sc_journal_copying = 1;
		GJ_DEBUG(1, "Starting copy of journal.");
		g_journal_metadata_update(sc);
	}
	g_journal_copy_send(sc);
}