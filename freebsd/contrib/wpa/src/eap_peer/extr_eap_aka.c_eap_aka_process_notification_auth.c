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
typedef  int /*<<< orphan*/  u8 ;
struct wpabuf {int dummy; } ;
struct eap_sim_attrs {int /*<<< orphan*/ * mac; } ;
struct eap_aka_data {scalar_t__ reauth; } ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_INFO ; 
 int /*<<< orphan*/  MSG_WARNING ; 
 scalar_t__ eap_aka_process_notification_reauth (struct eap_aka_data*,struct eap_sim_attrs*) ; 
 scalar_t__ eap_aka_verify_mac (struct eap_aka_data*,struct wpabuf const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int eap_aka_process_notification_auth(struct eap_aka_data *data,
					     const struct wpabuf *reqData,
					     struct eap_sim_attrs *attr)
{
	if (attr->mac == NULL) {
		wpa_printf(MSG_INFO, "EAP-AKA: no AT_MAC in after_auth "
			   "Notification message");
		return -1;
	}

	if (eap_aka_verify_mac(data, reqData, attr->mac, (u8 *) "", 0)) {
		wpa_printf(MSG_WARNING, "EAP-AKA: Notification message "
			   "used invalid AT_MAC");
		return -1;
	}

	if (data->reauth &&
	    eap_aka_process_notification_reauth(data, attr)) {
		wpa_printf(MSG_WARNING, "EAP-AKA: Invalid notification "
			   "message after reauth");
		return -1;
	}

	return 0;
}