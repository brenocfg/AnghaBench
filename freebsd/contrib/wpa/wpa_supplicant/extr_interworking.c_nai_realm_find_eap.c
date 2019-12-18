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
typedef  size_t u8 ;
struct wpa_supplicant {int dummy; } ;
struct wpa_cred {char* username; char* password; char* private_key; } ;
struct nai_realm_eap {int dummy; } ;
struct nai_realm {size_t eap_count; struct nai_realm_eap* eap; } ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_DEBUG ; 
 scalar_t__ nai_realm_cred_cert (struct wpa_supplicant*,struct nai_realm_eap*) ; 
 scalar_t__ nai_realm_cred_username (struct wpa_supplicant*,struct nai_realm_eap*) ; 
 int /*<<< orphan*/  wpa_msg (struct wpa_supplicant*,int /*<<< orphan*/ ,char*,char*,char*,char*) ; 

__attribute__((used)) static struct nai_realm_eap * nai_realm_find_eap(struct wpa_supplicant *wpa_s,
						 struct wpa_cred *cred,
						 struct nai_realm *realm)
{
	u8 e;

	if (cred->username == NULL ||
	    cred->username[0] == '\0' ||
	    ((cred->password == NULL ||
	      cred->password[0] == '\0') &&
	     (cred->private_key == NULL ||
	      cred->private_key[0] == '\0'))) {
		wpa_msg(wpa_s, MSG_DEBUG,
			"nai-realm-find-eap: incomplete cred info: username: %s  password: %s private_key: %s",
			cred->username ? cred->username : "NULL",
			cred->password ? cred->password : "NULL",
			cred->private_key ? cred->private_key : "NULL");
		return NULL;
	}

	for (e = 0; e < realm->eap_count; e++) {
		struct nai_realm_eap *eap = &realm->eap[e];
		if (cred->password && cred->password[0] &&
		    nai_realm_cred_username(wpa_s, eap))
			return eap;
		if (cred->private_key && cred->private_key[0] &&
		    nai_realm_cred_cert(wpa_s, eap))
			return eap;
	}

	return NULL;
}