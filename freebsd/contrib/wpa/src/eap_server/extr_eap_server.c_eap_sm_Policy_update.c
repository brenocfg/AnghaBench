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
typedef  int /*<<< orphan*/  u8 ;
struct eap_sm {int /*<<< orphan*/  decision; TYPE_1__* user; } ;
struct TYPE_2__ {scalar_t__ phase2; } ;

/* Variables and functions */
 int /*<<< orphan*/  DECISION_FAILURE ; 
 int /*<<< orphan*/  MSG_DEBUG ; 
 int /*<<< orphan*/  eap_sm_process_nak (struct eap_sm*,int /*<<< orphan*/  const*,size_t) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void eap_sm_Policy_update(struct eap_sm *sm, const u8 *nak_list,
				 size_t len)
{
	if (nak_list == NULL || sm == NULL || sm->user == NULL)
		return;

	if (sm->user->phase2) {
		wpa_printf(MSG_DEBUG, "EAP: EAP-Nak received after Phase2 user"
			   " info was selected - reject");
		sm->decision = DECISION_FAILURE;
		return;
	}

	eap_sm_process_nak(sm, nak_list, len);
}