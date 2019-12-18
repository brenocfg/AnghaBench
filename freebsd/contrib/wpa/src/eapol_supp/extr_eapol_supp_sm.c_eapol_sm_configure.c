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
struct eapol_sm {int heldPeriod; int authPeriod; int startPeriod; int maxStart; } ;

/* Variables and functions */

void eapol_sm_configure(struct eapol_sm *sm, int heldPeriod, int authPeriod,
			int startPeriod, int maxStart)
{
	if (sm == NULL)
		return;
	if (heldPeriod >= 0)
		sm->heldPeriod = heldPeriod;
	if (authPeriod >= 0)
		sm->authPeriod = authPeriod;
	if (startPeriod >= 0)
		sm->startPeriod = startPeriod;
	if (maxStart >= 0)
		sm->maxStart = maxStart;
}