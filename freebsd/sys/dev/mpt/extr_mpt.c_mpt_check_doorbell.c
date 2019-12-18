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
typedef  int /*<<< orphan*/  uint32_t ;
struct mpt_softc {int dummy; } ;

/* Variables and functions */
 scalar_t__ MPT_DB_STATE_RUNNING ; 
 scalar_t__ MPT_STATE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mpt_print_db (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mpt_prt (struct mpt_softc*,char*) ; 
 int /*<<< orphan*/  mpt_rd_db (struct mpt_softc*) ; 

void
mpt_check_doorbell(struct mpt_softc *mpt)
{
	uint32_t db = mpt_rd_db(mpt);

	if (MPT_STATE(db) != MPT_DB_STATE_RUNNING) {
		mpt_prt(mpt, "Device not running\n");
		mpt_print_db(db);
	}
}