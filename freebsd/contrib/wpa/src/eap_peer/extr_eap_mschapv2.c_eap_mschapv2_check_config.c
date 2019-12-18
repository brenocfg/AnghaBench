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
struct eap_sm {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_INFO ; 
 int /*<<< orphan*/ * eap_get_config_identity (struct eap_sm*,size_t*) ; 
 int /*<<< orphan*/ * eap_get_config_password (struct eap_sm*,size_t*) ; 
 int /*<<< orphan*/  eap_sm_request_identity (struct eap_sm*) ; 
 int /*<<< orphan*/  eap_sm_request_password (struct eap_sm*) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int eap_mschapv2_check_config(struct eap_sm *sm)
{
	size_t len;

	if (eap_get_config_identity(sm, &len) == NULL) {
		wpa_printf(MSG_INFO, "EAP-MSCHAPV2: Identity not configured");
		eap_sm_request_identity(sm);
		return -1;
	}

	if (eap_get_config_password(sm, &len) == NULL) {
		wpa_printf(MSG_INFO, "EAP-MSCHAPV2: Password not configured");
		eap_sm_request_password(sm);
		return -1;
	}

	return 0;
}