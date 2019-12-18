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
struct eapol_sm {scalar_t__ portEnabled; int /*<<< orphan*/  force_authorized_update; } ;
typedef  scalar_t__ Boolean ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_DEBUG ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  eapol_sm_step (struct eapol_sm*) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,scalar_t__) ; 

void eapol_sm_notify_portEnabled(struct eapol_sm *sm, Boolean enabled)
{
	if (sm == NULL)
		return;
	wpa_printf(MSG_DEBUG, "EAPOL: External notification - "
		   "portEnabled=%d", enabled);
	if (sm->portEnabled != enabled)
		sm->force_authorized_update = TRUE;
	sm->portEnabled = enabled;
	eapol_sm_step(sm);
}