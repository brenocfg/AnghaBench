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
 int AUC_DISABLED ; 
 int AUC_NOAUDIT ; 
 int /*<<< orphan*/  AUD_STATE_DISABLED ; 
 int /*<<< orphan*/  AUD_STATE_ENABLED ; 
 scalar_t__ ENOSYS ; 
 scalar_t__ audit_get_cond (int*) ; 
 int /*<<< orphan*/  auditd_log_err (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  auditing_state ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  strerror (scalar_t__) ; 

__attribute__((used)) static void
init_audit_state(void)
{
	int au_cond;

	if (audit_get_cond(&au_cond) < 0) {
		if (errno != ENOSYS) {
			auditd_log_err("Audit status check failed (%s)",
			    strerror(errno));
		}
		auditing_state = AUD_STATE_DISABLED;
	} else
		if (au_cond == AUC_NOAUDIT || au_cond == AUC_DISABLED)
			auditing_state = AUD_STATE_DISABLED;
		else
			auditing_state = AUD_STATE_ENABLED;
}