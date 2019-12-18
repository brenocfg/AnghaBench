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
typedef  int uint8_t ;
struct ncr53c9x_tinfo {int dummy; } ;
struct ncr53c9x_softc {scalar_t__ sc_rev; int sc_selid; int sc_id; int /*<<< orphan*/  sc_dleft; int /*<<< orphan*/  sc_dp; struct ncr53c9x_ecb* sc_nexus; int /*<<< orphan*/  sc_state; int /*<<< orphan*/  sc_dev; struct ncr53c9x_tinfo* sc_tinfo; } ;
struct ncr53c9x_linfo {struct ncr53c9x_ecb** queued; struct ncr53c9x_ecb* untagged; scalar_t__ busy; } ;
struct ncr53c9x_ecb {int flags; int /*<<< orphan*/  dleft; int /*<<< orphan*/  daddr; } ;

/* Variables and functions */
 int ECB_ABORT ; 
 int ECB_RESET ; 
 int /*<<< orphan*/  MA_OWNED ; 
 int MSG_SIMPLE_Q_TAG ; 
 int /*<<< orphan*/  NCR_CONNECTED ; 
 int /*<<< orphan*/  NCR_IDENTIFIED ; 
 int /*<<< orphan*/  NCR_LOCK_ASSERT (struct ncr53c9x_softc*,int /*<<< orphan*/ ) ; 
 scalar_t__ NCR_VARIANT_FAS366 ; 
 int /*<<< orphan*/  SEND_ABORT ; 
 int /*<<< orphan*/  SEND_DEV_RESET ; 
 struct ncr53c9x_linfo* TINFO_LUN (struct ncr53c9x_tinfo*,int) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,int,...) ; 
 int ffs (int) ; 
 int /*<<< orphan*/  ncr53c9x_sched_msgout (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ncr53c9x_setsync (struct ncr53c9x_softc*,struct ncr53c9x_tinfo*) ; 

__attribute__((used)) static int
ncr53c9x_reselect(struct ncr53c9x_softc *sc, int message, int tagtype,
    int tagid)
{
	struct ncr53c9x_ecb *ecb = NULL;
	struct ncr53c9x_linfo *li;
	struct ncr53c9x_tinfo *ti;
	uint8_t lun, selid, target;

	NCR_LOCK_ASSERT(sc, MA_OWNED);

	if (sc->sc_rev == NCR_VARIANT_FAS366)
		target = sc->sc_selid;
	else {
		/*
		 * The SCSI chip made a snapshot of the data bus
		 * while the reselection was being negotiated.
		 * This enables us to determine which target did
		 * the reselect.
		 */
		selid = sc->sc_selid & ~(1 << sc->sc_id);
		if (selid & (selid - 1)) {
			device_printf(sc->sc_dev, "reselect with invalid "
			    "selid %02x; sending DEVICE RESET\n", selid);
			goto reset;
		}

		target = ffs(selid) - 1;
	}
	lun = message & 0x07;

	/*
	 * Search wait queue for disconnected command.
	 * The list should be short, so I haven't bothered with
	 * any more sophisticated structures than a simple
	 * singly linked list.
	 */
	ti = &sc->sc_tinfo[target];
	li = TINFO_LUN(ti, lun);

	/*
	 * We can get as far as the LUN with the IDENTIFY
	 * message.  Check to see if we're running an
	 * untagged command.  Otherwise ack the IDENTIFY
	 * and wait for a tag message.
	 */
	if (li != NULL) {
		if (li->untagged != NULL && li->busy)
			ecb = li->untagged;
		else if (tagtype != MSG_SIMPLE_Q_TAG) {
			/* Wait for tag to come by. */
			sc->sc_state = NCR_IDENTIFIED;
			return (0);
		} else if (tagtype)
			ecb = li->queued[tagid];
	}
	if (ecb == NULL) {
		device_printf(sc->sc_dev, "reselect from target %d lun %d "
		    "tag %x:%x with no nexus; sending ABORT\n",
		    target, lun, tagtype, tagid);
		goto abort;
	}

	/* Make this nexus active again. */
	sc->sc_state = NCR_CONNECTED;
	sc->sc_nexus = ecb;
	ncr53c9x_setsync(sc, ti);

	if (ecb->flags & ECB_RESET)
		ncr53c9x_sched_msgout(SEND_DEV_RESET);
	else if (ecb->flags & ECB_ABORT)
		ncr53c9x_sched_msgout(SEND_ABORT);

	/* Do an implicit RESTORE POINTERS. */
	sc->sc_dp = ecb->daddr;
	sc->sc_dleft = ecb->dleft;

	return (0);

reset:
	ncr53c9x_sched_msgout(SEND_DEV_RESET);
	return (1);

abort:
	ncr53c9x_sched_msgout(SEND_ABORT);
	return (1);
}