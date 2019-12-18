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
typedef  int uint64_t ;
typedef  int /*<<< orphan*/  uint32_t ;
struct ntb_softc {int db_link_mask; int fake_db; int force_db; int db_mask; int db_valid_mask; int /*<<< orphan*/  device; int /*<<< orphan*/  last_ts; } ;

/* Variables and functions */
 int /*<<< orphan*/  DB_MASK_LOCK (struct ntb_softc*) ; 
 int /*<<< orphan*/  DB_MASK_UNLOCK (struct ntb_softc*) ; 
 scalar_t__ HAS_FEATURE (struct ntb_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NTB_SB01BASE_LOCKUP ; 
 scalar_t__ intel_ntb_poll_link (struct ntb_softc*) ; 
 int intel_ntb_vec_mask (struct ntb_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ntb_db_event (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ntb_link_event (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ticks ; 

__attribute__((used)) static void
intel_ntb_interrupt(struct ntb_softc *ntb, uint32_t vec)
{
	uint64_t vec_mask;

	ntb->last_ts = ticks;
	vec_mask = intel_ntb_vec_mask(ntb, vec);

	if ((vec_mask & ntb->db_link_mask) != 0) {
		if (intel_ntb_poll_link(ntb))
			ntb_link_event(ntb->device);
	}

	if (HAS_FEATURE(ntb, NTB_SB01BASE_LOCKUP) &&
	    (vec_mask & ntb->db_link_mask) == 0) {
		DB_MASK_LOCK(ntb);

		/*
		 * Do not report same DB events again if not cleared yet,
		 * unless the mask was just cleared for them and this
		 * interrupt handler call can be the consequence of it.
		 */
		vec_mask &= ~ntb->fake_db | ntb->force_db;
		ntb->force_db &= ~vec_mask;

		/* Update our internal doorbell register. */
		ntb->fake_db |= vec_mask;

		/* Do not report masked DB events. */
		vec_mask &= ~ntb->db_mask;

		DB_MASK_UNLOCK(ntb);
	}

	if ((vec_mask & ntb->db_valid_mask) != 0)
		ntb_db_event(ntb->device, vec);
}