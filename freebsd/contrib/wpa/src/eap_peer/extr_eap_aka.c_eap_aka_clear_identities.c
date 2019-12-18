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
struct eap_aka_data {scalar_t__ last_eap_identity_len; int /*<<< orphan*/ * last_eap_identity; scalar_t__ reauth_id_len; int /*<<< orphan*/ * reauth_id; scalar_t__ use_pseudonym; scalar_t__ pseudonym_len; int /*<<< orphan*/ * pseudonym; } ;

/* Variables and functions */
 int CLEAR_EAP_ID ; 
 int CLEAR_PSEUDONYM ; 
 int CLEAR_REAUTH_ID ; 
 int /*<<< orphan*/  MSG_DEBUG ; 
 int /*<<< orphan*/  eap_set_anon_id (struct eap_sm*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  os_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void eap_aka_clear_identities(struct eap_sm *sm,
				     struct eap_aka_data *data, int id)
{
	if ((id & CLEAR_PSEUDONYM) && data->pseudonym) {
		wpa_printf(MSG_DEBUG, "EAP-AKA: forgetting old pseudonym");
		os_free(data->pseudonym);
		data->pseudonym = NULL;
		data->pseudonym_len = 0;
		if (data->use_pseudonym)
			eap_set_anon_id(sm, NULL, 0);
	}
	if ((id & CLEAR_REAUTH_ID) && data->reauth_id) {
		wpa_printf(MSG_DEBUG, "EAP-AKA: forgetting old reauth_id");
		os_free(data->reauth_id);
		data->reauth_id = NULL;
		data->reauth_id_len = 0;
	}
	if ((id & CLEAR_EAP_ID) && data->last_eap_identity) {
		wpa_printf(MSG_DEBUG, "EAP-AKA: forgetting old eap_id");
		os_free(data->last_eap_identity);
		data->last_eap_identity = NULL;
		data->last_eap_identity_len = 0;
	}
}