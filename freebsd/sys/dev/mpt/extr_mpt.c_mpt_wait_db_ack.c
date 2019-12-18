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
struct mpt_softc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DELAY (int) ; 
 int /*<<< orphan*/  MPT_DB_IS_BUSY (int /*<<< orphan*/ ) ; 
 int MPT_FAIL ; 
 int MPT_MAX_WAIT ; 
 int MPT_OK ; 
 int maxwait_ack ; 
 int /*<<< orphan*/  mpt_rd_intr (struct mpt_softc*) ; 

__attribute__((used)) static int
mpt_wait_db_ack(struct mpt_softc *mpt)
{
	int i;

	for (i=0; i < MPT_MAX_WAIT; i++) {
		if (!MPT_DB_IS_BUSY(mpt_rd_intr(mpt))) {
			maxwait_ack = i > maxwait_ack ? i : maxwait_ack;
			return (MPT_OK);
		}
		DELAY(200);
	}
	return (MPT_FAIL);
}