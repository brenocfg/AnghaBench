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
struct wpabuf {int dummy; } ;
struct wpa_supplicant {char* imsi; int mnc_len; scalar_t__ scard; } ;
struct wpa_cred {char* imsi; char** domain; size_t num_domain; scalar_t__ pcsc; } ;
typedef  int /*<<< orphan*/  nai ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_DEBUG ; 
 scalar_t__ build_root_nai (char*,int,char*,int,int /*<<< orphan*/ ) ; 
 scalar_t__ domain_name_list_contains (struct wpabuf*,char*,int) ; 
 scalar_t__ interworking_pcsc_read_imsi (struct wpa_supplicant*) ; 
 char* os_strchr (char*,char) ; 
 int /*<<< orphan*/  wpa_msg (struct wpa_supplicant*,int /*<<< orphan*/ ,char*,char*) ; 

int interworking_home_sp_cred(struct wpa_supplicant *wpa_s,
			      struct wpa_cred *cred,
			      struct wpabuf *domain_names)
{
	size_t i;
	int ret = -1;
#ifdef INTERWORKING_3GPP
	char nai[100], *realm;

	char *imsi = NULL;
	int mnc_len = 0;
	if (cred->imsi)
		imsi = cred->imsi;
#ifdef PCSC_FUNCS
	else if (cred->pcsc && wpa_s->scard) {
		if (interworking_pcsc_read_imsi(wpa_s) < 0)
			return -1;
		imsi = wpa_s->imsi;
		mnc_len = wpa_s->mnc_len;
	}
#endif /* PCSC_FUNCS */
#ifdef CONFIG_EAP_PROXY
	else if (cred->pcsc && wpa_s->mnc_len > 0 && wpa_s->imsi[0]) {
		imsi = wpa_s->imsi;
		mnc_len = wpa_s->mnc_len;
	}
#endif /* CONFIG_EAP_PROXY */
	if (domain_names &&
	    imsi && build_root_nai(nai, sizeof(nai), imsi, mnc_len, 0) == 0) {
		realm = os_strchr(nai, '@');
		if (realm)
			realm++;
		wpa_msg(wpa_s, MSG_DEBUG,
			"Interworking: Search for match with SIM/USIM domain %s",
			realm);
		if (realm &&
		    domain_name_list_contains(domain_names, realm, 1))
			return 1;
		if (realm)
			ret = 0;
	}
#endif /* INTERWORKING_3GPP */

	if (domain_names == NULL || cred->domain == NULL)
		return ret;

	for (i = 0; i < cred->num_domain; i++) {
		wpa_msg(wpa_s, MSG_DEBUG,
			"Interworking: Search for match with home SP FQDN %s",
			cred->domain[i]);
		if (domain_name_list_contains(domain_names, cred->domain[i], 1))
			return 1;
	}

	return 0;
}