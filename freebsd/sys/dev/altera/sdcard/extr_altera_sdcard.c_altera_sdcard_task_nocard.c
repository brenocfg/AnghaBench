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
 int /*<<< orphan*/  ALTERA_SDCARD_STATE_BADCARD ; 
 int /*<<< orphan*/  ALTERA_SDCARD_STATE_DETACHED ; 
 int /*<<< orphan*/  ALTERA_SDCARD_STATE_IDLE ; 
 int /*<<< orphan*/  altera_sdcard_disk_insert (struct altera_sdcard_softc*) ; 
 int altera_sdcard_read_asr (struct altera_sdcard_softc*) ; 
 scalar_t__ altera_sdcard_read_csd (struct altera_sdcard_softc*) ; 

__attribute__((used)) static void
altera_sdcard_task_nocard(struct altera_sdcard_softc *sc)
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
	 * If there is no card insertion, remain in NOCARD.
	 */
	if (!(altera_sdcard_read_asr(sc) & ALTERA_SDCARD_ASR_CARDPRESENT))
		return;

	/*
	 * Read the CSD -- it may contain values that the driver can't handle,
	 * either because of an unsupported version/feature, or because the
	 * card is misbehaving.  This triggers a transition to
	 * ALTERA_SDCARD_STATE_BADCARD.  We rely on the CSD read to print a
	 * banner about how the card is problematic, since it has more
	 * information.  The bad card state allows us to print that banner
	 * once rather than each time we notice the card is there, and still
	 * bad.
	 */
	if (altera_sdcard_read_csd(sc) != 0) {
		sc->as_state = ALTERA_SDCARD_STATE_BADCARD;
		return;
	}

	/*
	 * Process card insertion and upgrade to the IDLE state.
	 */
	altera_sdcard_disk_insert(sc);
	sc->as_state = ALTERA_SDCARD_STATE_IDLE;
}