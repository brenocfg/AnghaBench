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
#define  EAP_SIM_GENERAL_FAILURE_AFTER_AUTH 132 
#define  EAP_SIM_GENERAL_FAILURE_BEFORE_AUTH 131 
#define  EAP_SIM_NOT_SUBSCRIBED 130 
#define  EAP_SIM_SUCCESS 129 
#define  EAP_SIM_TEMPORARILY_DENIED 128 
 int /*<<< orphan*/  MSG_INFO ; 
 int /*<<< orphan*/  MSG_WARNING ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,char const*,...) ; 

void eap_sim_report_notification(void *msg_ctx, int notification, int aka)
{
#ifndef CONFIG_NO_STDOUT_DEBUG
	const char *type = aka ? "AKA" : "SIM";
#endif /* CONFIG_NO_STDOUT_DEBUG */

	switch (notification) {
	case EAP_SIM_GENERAL_FAILURE_AFTER_AUTH:
		wpa_printf(MSG_WARNING, "EAP-%s: General failure "
			   "notification (after authentication)", type);
		break;
	case EAP_SIM_TEMPORARILY_DENIED:
		wpa_printf(MSG_WARNING, "EAP-%s: Failure notification: "
			   "User has been temporarily denied access to the "
			   "requested service", type);
		break;
	case EAP_SIM_NOT_SUBSCRIBED:
		wpa_printf(MSG_WARNING, "EAP-%s: Failure notification: "
			   "User has not subscribed to the requested service",
			   type);
		break;
	case EAP_SIM_GENERAL_FAILURE_BEFORE_AUTH:
		wpa_printf(MSG_WARNING, "EAP-%s: General failure "
			   "notification (before authentication)", type);
		break;
	case EAP_SIM_SUCCESS:
		wpa_printf(MSG_INFO, "EAP-%s: Successful authentication "
			   "notification", type);
		break;
	default:
		if (notification >= 32768) {
			wpa_printf(MSG_INFO, "EAP-%s: Unrecognized "
				   "non-failure notification %d",
				   type, notification);
		} else {
			wpa_printf(MSG_WARNING, "EAP-%s: Unrecognized "
				   "failure notification %d",
				   type, notification);
		}
	}
}