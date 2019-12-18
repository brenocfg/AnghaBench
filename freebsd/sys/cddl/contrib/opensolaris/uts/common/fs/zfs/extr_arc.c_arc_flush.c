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
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int /*<<< orphan*/  spa_t ;
typedef  int /*<<< orphan*/  boolean_t ;

/* Variables and functions */
 int /*<<< orphan*/  ARC_BUFC_DATA ; 
 int /*<<< orphan*/  ARC_BUFC_METADATA ; 
 int /*<<< orphan*/  ASSERT (int) ; 
 int /*<<< orphan*/  arc_flush_state (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  arc_mfu ; 
 int /*<<< orphan*/  arc_mfu_ghost ; 
 int /*<<< orphan*/  arc_mru ; 
 int /*<<< orphan*/  arc_mru_ghost ; 
 int /*<<< orphan*/  spa_load_guid (int /*<<< orphan*/ *) ; 

void
arc_flush(spa_t *spa, boolean_t retry)
{
	uint64_t guid = 0;

	/*
	 * If retry is B_TRUE, a spa must not be specified since we have
	 * no good way to determine if all of a spa's buffers have been
	 * evicted from an arc state.
	 */
	ASSERT(!retry || spa == 0);

	if (spa != NULL)
		guid = spa_load_guid(spa);

	(void) arc_flush_state(arc_mru, guid, ARC_BUFC_DATA, retry);
	(void) arc_flush_state(arc_mru, guid, ARC_BUFC_METADATA, retry);

	(void) arc_flush_state(arc_mfu, guid, ARC_BUFC_DATA, retry);
	(void) arc_flush_state(arc_mfu, guid, ARC_BUFC_METADATA, retry);

	(void) arc_flush_state(arc_mru_ghost, guid, ARC_BUFC_DATA, retry);
	(void) arc_flush_state(arc_mru_ghost, guid, ARC_BUFC_METADATA, retry);

	(void) arc_flush_state(arc_mfu_ghost, guid, ARC_BUFC_DATA, retry);
	(void) arc_flush_state(arc_mfu_ghost, guid, ARC_BUFC_METADATA, retry);
}