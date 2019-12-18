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
struct eapol_sm {int /*<<< orphan*/  portValid; } ;
typedef  int /*<<< orphan*/  Boolean ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_DEBUG ; 
 int /*<<< orphan*/  eapol_sm_step (struct eapol_sm*) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 

void eapol_sm_notify_portValid(struct eapol_sm *sm, Boolean valid)
{
	if (sm == NULL)
		return;
	wpa_printf(MSG_DEBUG, "EAPOL: External notification - "
		   "portValid=%d", valid);
	sm->portValid = valid;
	eapol_sm_step(sm);
}