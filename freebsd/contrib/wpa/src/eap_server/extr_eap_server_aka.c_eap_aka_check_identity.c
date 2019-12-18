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
struct eap_sm {int /*<<< orphan*/  eap_sim_db_priv; int /*<<< orphan*/  identity_len; int /*<<< orphan*/  identity; } ;
struct eap_aka_data {scalar_t__ eap_method; int /*<<< orphan*/  permanent; } ;

/* Variables and functions */
 char EAP_AKA_PRIME_PSEUDONYM_PREFIX ; 
 char EAP_AKA_PSEUDONYM_PREFIX ; 
 scalar_t__ EAP_TYPE_AKA ; 
 scalar_t__ EAP_TYPE_AKA_PRIME ; 
 int /*<<< orphan*/  MSG_DEBUG ; 
 scalar_t__ eap_aka_check_identity_reauth (struct eap_sm*,struct eap_aka_data*,char*) ; 
 int /*<<< orphan*/  eap_aka_fullauth (struct eap_sm*,struct eap_aka_data*) ; 
 char* eap_sim_db_get_permanent (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  os_free (char*) ; 
 int /*<<< orphan*/  os_strlcpy (int /*<<< orphan*/ ,char const*,int) ; 
 char* sim_get_username (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,...) ; 

__attribute__((used)) static void eap_aka_check_identity(struct eap_sm *sm,
				   struct eap_aka_data *data)
{
	char *username;

	/* Check if we already know the identity from EAP-Response/Identity */

	username = sim_get_username(sm->identity, sm->identity_len);
	if (username == NULL)
		return;

	if (eap_aka_check_identity_reauth(sm, data, username) > 0) {
		os_free(username);
		/*
		 * Since re-auth username was recognized, skip AKA/Identity
		 * exchange.
		 */
		return;
	}

	if ((data->eap_method == EAP_TYPE_AKA_PRIME &&
	     username[0] == EAP_AKA_PRIME_PSEUDONYM_PREFIX) ||
	    (data->eap_method == EAP_TYPE_AKA &&
	     username[0] == EAP_AKA_PSEUDONYM_PREFIX)) {
		const char *permanent;
		wpa_printf(MSG_DEBUG, "EAP-AKA: Pseudonym username '%s'",
			   username);
		permanent = eap_sim_db_get_permanent(
			sm->eap_sim_db_priv, username);
		if (permanent == NULL) {
			os_free(username);
			wpa_printf(MSG_DEBUG, "EAP-AKA: Unknown pseudonym "
				   "identity - request permanent identity");
			/* Remain in IDENTITY state for another round */
			return;
		}
		os_strlcpy(data->permanent, permanent,
			   sizeof(data->permanent));
		/*
		 * Since pseudonym username was recognized, skip AKA/Identity
		 * exchange.
		 */
		eap_aka_fullauth(sm, data);
	}

	os_free(username);
}