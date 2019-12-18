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
struct wpa_global {int /*<<< orphan*/ * p2p_init_wpa_s; } ;

/* Variables and functions */
 scalar_t__ os_strcmp (char*,char const*) ; 
 int /*<<< orphan*/  os_strlen (char const*) ; 
 scalar_t__ os_strncmp (char*,char const*,int /*<<< orphan*/ ) ; 
 char* wpa_supplicant_ctrl_iface_process (int /*<<< orphan*/ *,char*,size_t*) ; 

__attribute__((used)) static char * wpas_global_ctrl_iface_redir_p2p(struct wpa_global *global,
					       char *buf, size_t *resp_len)
{
#ifdef CONFIG_P2P
	static const char * cmd[] = {
		"LIST_NETWORKS",
		"P2P_FIND",
		"P2P_STOP_FIND",
		"P2P_LISTEN",
		"P2P_GROUP_ADD",
		"P2P_GET_PASSPHRASE",
		"P2P_SERVICE_UPDATE",
		"P2P_SERVICE_FLUSH",
		"P2P_FLUSH",
		"P2P_CANCEL",
		"P2P_PRESENCE_REQ",
		"P2P_EXT_LISTEN",
#ifdef CONFIG_AP
		"STA-FIRST",
#endif /* CONFIG_AP */
		NULL
	};
	static const char * prefix[] = {
#ifdef ANDROID
		"DRIVER ",
#endif /* ANDROID */
		"GET_CAPABILITY ",
		"GET_NETWORK ",
		"REMOVE_NETWORK ",
		"P2P_FIND ",
		"P2P_CONNECT ",
		"P2P_LISTEN ",
		"P2P_GROUP_REMOVE ",
		"P2P_GROUP_ADD ",
		"P2P_GROUP_MEMBER ",
		"P2P_PROV_DISC ",
		"P2P_SERV_DISC_REQ ",
		"P2P_SERV_DISC_CANCEL_REQ ",
		"P2P_SERV_DISC_RESP ",
		"P2P_SERV_DISC_EXTERNAL ",
		"P2P_SERVICE_ADD ",
		"P2P_SERVICE_DEL ",
		"P2P_SERVICE_REP ",
		"P2P_REJECT ",
		"P2P_INVITE ",
		"P2P_PEER ",
		"P2P_SET ",
		"P2P_UNAUTHORIZE ",
		"P2P_PRESENCE_REQ ",
		"P2P_EXT_LISTEN ",
		"P2P_REMOVE_CLIENT ",
		"WPS_NFC_TOKEN ",
		"WPS_NFC_TAG_READ ",
		"NFC_GET_HANDOVER_SEL ",
		"NFC_GET_HANDOVER_REQ ",
		"NFC_REPORT_HANDOVER ",
		"P2P_ASP_PROVISION ",
		"P2P_ASP_PROVISION_RESP ",
#ifdef CONFIG_AP
		"STA ",
		"STA-NEXT ",
#endif /* CONFIG_AP */
		NULL
	};
	int found = 0;
	int i;

	if (global->p2p_init_wpa_s == NULL)
		return NULL;

	for (i = 0; !found && cmd[i]; i++) {
		if (os_strcmp(buf, cmd[i]) == 0)
			found = 1;
	}

	for (i = 0; !found && prefix[i]; i++) {
		if (os_strncmp(buf, prefix[i], os_strlen(prefix[i])) == 0)
			found = 1;
	}

	if (found)
		return wpa_supplicant_ctrl_iface_process(global->p2p_init_wpa_s,
							 buf, resp_len);
#endif /* CONFIG_P2P */
	return NULL;
}