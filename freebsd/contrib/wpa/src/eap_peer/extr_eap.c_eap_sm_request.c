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
struct eap_sm {int /*<<< orphan*/  eapol_ctx; TYPE_1__* eapol_cb; } ;
struct eap_peer_config {char* pending_req_otp; size_t pending_req_otp_len; int /*<<< orphan*/  pending_req_sim; int /*<<< orphan*/  pending_req_passphrase; int /*<<< orphan*/  pending_req_pin; int /*<<< orphan*/  pending_req_new_password; int /*<<< orphan*/  pending_req_password; int /*<<< orphan*/  pending_req_identity; } ;
typedef  enum wpa_ctrl_req_type { ____Placeholder_wpa_ctrl_req_type } wpa_ctrl_req_type ;
struct TYPE_2__ {int /*<<< orphan*/  (* eap_param_needed ) (int /*<<< orphan*/ ,int,char const*) ;} ;

/* Variables and functions */
#define  WPA_CTRL_REQ_EAP_IDENTITY 135 
#define  WPA_CTRL_REQ_EAP_NEW_PASSWORD 134 
#define  WPA_CTRL_REQ_EAP_OTP 133 
#define  WPA_CTRL_REQ_EAP_PASSPHRASE 132 
#define  WPA_CTRL_REQ_EAP_PASSWORD 131 
#define  WPA_CTRL_REQ_EAP_PIN 130 
#define  WPA_CTRL_REQ_EXT_CERT_CHECK 129 
#define  WPA_CTRL_REQ_SIM 128 
 struct eap_peer_config* eap_get_config (struct eap_sm*) ; 
 int /*<<< orphan*/  os_free (char*) ; 
 char* os_malloc (size_t) ; 
 int /*<<< orphan*/  os_memcpy (char*,char const*,size_t) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int,char const*) ; 

__attribute__((used)) static void eap_sm_request(struct eap_sm *sm, enum wpa_ctrl_req_type field,
			   const char *msg, size_t msglen)
{
#if defined(CONFIG_CTRL_IFACE) || !defined(CONFIG_NO_STDOUT_DEBUG)
	struct eap_peer_config *config;
	const char *txt = NULL;
	char *tmp;

	if (sm == NULL)
		return;
	config = eap_get_config(sm);
	if (config == NULL)
		return;

	switch (field) {
	case WPA_CTRL_REQ_EAP_IDENTITY:
		config->pending_req_identity++;
		break;
	case WPA_CTRL_REQ_EAP_PASSWORD:
		config->pending_req_password++;
		break;
	case WPA_CTRL_REQ_EAP_NEW_PASSWORD:
		config->pending_req_new_password++;
		break;
	case WPA_CTRL_REQ_EAP_PIN:
		config->pending_req_pin++;
		break;
	case WPA_CTRL_REQ_EAP_OTP:
		if (msg) {
			tmp = os_malloc(msglen + 3);
			if (tmp == NULL)
				return;
			tmp[0] = '[';
			os_memcpy(tmp + 1, msg, msglen);
			tmp[msglen + 1] = ']';
			tmp[msglen + 2] = '\0';
			txt = tmp;
			os_free(config->pending_req_otp);
			config->pending_req_otp = tmp;
			config->pending_req_otp_len = msglen + 3;
		} else {
			if (config->pending_req_otp == NULL)
				return;
			txt = config->pending_req_otp;
		}
		break;
	case WPA_CTRL_REQ_EAP_PASSPHRASE:
		config->pending_req_passphrase++;
		break;
	case WPA_CTRL_REQ_SIM:
		config->pending_req_sim++;
		txt = msg;
		break;
	case WPA_CTRL_REQ_EXT_CERT_CHECK:
		break;
	default:
		return;
	}

	if (sm->eapol_cb->eap_param_needed)
		sm->eapol_cb->eap_param_needed(sm->eapol_ctx, field, txt);
#endif /* CONFIG_CTRL_IFACE || !CONFIG_NO_STDOUT_DEBUG */
}