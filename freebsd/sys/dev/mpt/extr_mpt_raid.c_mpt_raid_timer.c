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
 int /*<<< orphan*/  MPT_LOCK_ASSERT (struct mpt_softc*) ; 
 int /*<<< orphan*/  mpt_raid_wakeup (struct mpt_softc*) ; 

__attribute__((used)) static void
mpt_raid_timer(void *arg)
{
	struct mpt_softc *mpt;

	mpt = (struct mpt_softc *)arg;
	MPT_LOCK_ASSERT(mpt);
	mpt_raid_wakeup(mpt);
}