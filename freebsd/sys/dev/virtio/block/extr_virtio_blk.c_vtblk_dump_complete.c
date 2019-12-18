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
struct vtblk_softc {int /*<<< orphan*/  vtblk_dump_queue; } ;

/* Variables and functions */
 int /*<<< orphan*/  VTBLK_LOCK (struct vtblk_softc*) ; 
 int /*<<< orphan*/  VTBLK_UNLOCK (struct vtblk_softc*) ; 
 int /*<<< orphan*/  vtblk_done_completed (struct vtblk_softc*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vtblk_dump_flush (struct vtblk_softc*) ; 

__attribute__((used)) static void
vtblk_dump_complete(struct vtblk_softc *sc)
{

	vtblk_dump_flush(sc);

	VTBLK_UNLOCK(sc);
	vtblk_done_completed(sc, &sc->vtblk_dump_queue);
	VTBLK_LOCK(sc);
}