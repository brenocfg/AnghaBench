#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  si_note; } ;
struct targ_softc {int /*<<< orphan*/  user_ccb_queue; TYPE_1__ read_select; } ;

/* Variables and functions */
 int /*<<< orphan*/  KNOTE_UNLOCKED (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PRIBIO ; 
 int /*<<< orphan*/  selwakeuppri (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wakeup (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
notify_user(struct targ_softc *softc)
{
	/*
	 * Notify users sleeping via poll(), kqueue(), and
	 * blocking read().
	 */
	selwakeuppri(&softc->read_select, PRIBIO);
	KNOTE_UNLOCKED(&softc->read_select.si_note, 0);
	wakeup(&softc->user_ccb_queue);
}