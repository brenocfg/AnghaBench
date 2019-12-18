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
 scalar_t__ AUD_STATE_INIT ; 
 int /*<<< orphan*/  __BSM_INTERNAL_NOTIFY_KEY ; 
 scalar_t__ auditing_state ; 
 int /*<<< orphan*/  init_audit_state () ; 
 int /*<<< orphan*/  notify_post (int /*<<< orphan*/ ) ; 

int
auditd_get_state(void)
{

	if (auditing_state == AUD_STATE_INIT) {
		init_audit_state();
		notify_post(__BSM_INTERNAL_NOTIFY_KEY);
	}

	return (auditing_state);
}