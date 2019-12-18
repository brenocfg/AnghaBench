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
struct altera_sdcard_softc {int as_flags; int /*<<< orphan*/  as_state; } ;

/* Variables and functions */
 int ALTERA_SDCARD_ASR_CARDPRESENT ; 
 int ALTERA_SDCARD_FLAG_DETACHREQ ; 
 int /*<<< orphan*/  ALTERA_SDCARD_LOCK_ASSERT (struct altera_sdcard_softc*) ; 
 int /*<<< orphan*/  ALTERA_SDCARD_STATE_DETACHED ; 
 int /*<<< orphan*/  ALTERA_SDCARD_STATE_NOCARD ; 
 int /*<<< orphan*/  altera_sdcard_disk_remove (struct altera_sdcard_softc*) ; 
 int altera_sdcard_read_asr (struct altera_sdcard_softc*) ; 

__attribute__((used)) static void
altera_sdcard_task_idle(struct altera_sdcard_softc *sc)
{

	ALTERA_SDCARD_LOCK_ASSERT(sc);

	/*
	 * Handle device driver detach.
	 */
	if (sc->as_flags & ALTERA_SDCARD_FLAG_DETACHREQ) {
		sc->as_state = ALTERA_SDCARD_STATE_DETACHED;
		return;
	}

	/*
	 * Handle safe card removal.
	 */
	if (!(altera_sdcard_read_asr(sc) & ALTERA_SDCARD_ASR_CARDPRESENT)) {
		altera_sdcard_disk_remove(sc);
		sc->as_state = ALTERA_SDCARD_STATE_NOCARD;
	}
}