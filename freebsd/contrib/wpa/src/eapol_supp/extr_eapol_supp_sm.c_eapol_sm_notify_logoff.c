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
struct eapol_sm {scalar_t__ startWhen; int /*<<< orphan*/  userLogoff; } ;
typedef  int /*<<< orphan*/  Boolean ;

/* Variables and functions */
 int /*<<< orphan*/  eapol_sm_step (struct eapol_sm*) ; 

void eapol_sm_notify_logoff(struct eapol_sm *sm, Boolean logoff)
{
	if (sm) {
		sm->userLogoff = logoff;
		if (!logoff) {
			/* If there is a delayed txStart queued, start now. */
			sm->startWhen = 0;
		}
		eapol_sm_step(sm);
	}
}