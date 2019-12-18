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

/* Variables and functions */
 int AUD_STATE_DISABLED ; 
 int AUD_STATE_ENABLED ; 
 int AUD_STATE_INIT ; 
 int /*<<< orphan*/  auditd_log_notice (char*) ; 
 int auditing_state ; 
 int /*<<< orphan*/  init_audit_state () ; 

void
auditd_set_state(int state)
{
	int old_auditing_state = auditing_state;

	if (state == AUD_STATE_INIT) 
		init_audit_state();
	else
		auditing_state = state;

	if (auditing_state != old_auditing_state) {
		if (auditing_state == AUD_STATE_ENABLED)
			auditd_log_notice("Auditing enabled");
		if (auditing_state == AUD_STATE_DISABLED)
			auditd_log_notice("Auditing disabled");
	}
}