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
typedef  scalar_t__ uint64_t ;
typedef  int /*<<< orphan*/  uint32_t ;

/* Variables and functions */
 int /*<<< orphan*/  OPAL_HANDLE_INTERRUPT ; 
 int /*<<< orphan*/  opal_call (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * opal_hb_proc ; 
 int /*<<< orphan*/  vtophys (scalar_t__*) ; 
 int /*<<< orphan*/  wakeup (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
opal_intr(void *xintr)
{
	uint64_t events = 0;

	opal_call(OPAL_HANDLE_INTERRUPT, (uint32_t)(uint64_t)xintr,
	    vtophys(&events));
	/* Wake up the heartbeat, if it's been setup. */
	if (events != 0 && opal_hb_proc != NULL)
		wakeup(opal_hb_proc);

}