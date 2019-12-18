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
struct eap_aka_data {scalar_t__ eap_method; int identity_round; void* notification; int /*<<< orphan*/  permanent; } ;

/* Variables and functions */
 char EAP_AKA_PERMANENT_PREFIX ; 
 char EAP_AKA_PRIME_PERMANENT_PREFIX ; 
 char EAP_AKA_PRIME_PSEUDONYM_PREFIX ; 
 char EAP_AKA_PRIME_REAUTH_ID_PREFIX ; 
 char EAP_AKA_PSEUDONYM_PREFIX ; 
 char EAP_AKA_REAUTH_ID_PREFIX ; 
 void* EAP_SIM_GENERAL_FAILURE_BEFORE_AUTH ; 
 scalar_t__ EAP_TYPE_AKA ; 
 scalar_t__ EAP_TYPE_AKA_PRIME ; 
 int /*<<< orphan*/  MSG_DEBUG ; 
 int /*<<< orphan*/  NOTIFICATION ; 
 scalar_t__ eap_aka_check_identity_reauth (struct eap_sm*,struct eap_aka_data*,char*) ; 
 int /*<<< orphan*/  eap_aka_fullauth (struct eap_sm*,struct eap_aka_data*) ; 
 int /*<<< orphan*/  eap_aka_state (struct eap_aka_data*,int /*<<< orphan*/ ) ; 
 char* eap_sim_db_get_permanent (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  os_free (char*) ; 
 int /*<<< orphan*/  os_strlcpy (int /*<<< orphan*/ ,char const*,int) ; 
 char* sim_get_username (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wpa_hexdump_ascii (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,...) ; 

__attribute__((used)) static void eap_aka_determine_identity(struct eap_sm *sm,
				       struct eap_aka_data *data)
{
	char *username;

	wpa_hexdump_ascii(MSG_DEBUG, "EAP-AKA: Identity",
			  sm->identity, sm->identity_len);

	username = sim_get_username(sm->identity, sm->identity_len);
	if (username == NULL) {
		data->notification = EAP_SIM_GENERAL_FAILURE_BEFORE_AUTH;
		eap_aka_state(data, NOTIFICATION);
		return;
	}

	if (eap_aka_check_identity_reauth(sm, data, username) > 0) {
		os_free(username);
		return;
	}

	if (((data->eap_method == EAP_TYPE_AKA_PRIME &&
	      username[0] == EAP_AKA_PRIME_REAUTH_ID_PREFIX) ||
	     (data->eap_method == EAP_TYPE_AKA &&
	      username[0] == EAP_AKA_REAUTH_ID_PREFIX)) &&
	    data->identity_round == 1) {
		/* Remain in IDENTITY state for another round to request full
		 * auth identity since we did not recognize reauth id */
		os_free(username);
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
		os_free(username);
		if (permanent == NULL) {
			wpa_printf(MSG_DEBUG, "EAP-AKA: Unknown pseudonym "
				   "identity - request permanent identity");
			/* Remain in IDENTITY state for another round */
			return;
		}
		os_strlcpy(data->permanent, permanent,
			   sizeof(data->permanent));
	} else if ((data->eap_method == EAP_TYPE_AKA_PRIME &&
		    username[0] == EAP_AKA_PRIME_PERMANENT_PREFIX) ||
		   (data->eap_method == EAP_TYPE_AKA &&
		    username[0] == EAP_AKA_PERMANENT_PREFIX)) {
		wpa_printf(MSG_DEBUG, "EAP-AKA: Permanent username '%s'",
			   username);
		os_strlcpy(data->permanent, username, sizeof(data->permanent));
		os_free(username);
	} else {
		wpa_printf(MSG_DEBUG, "EAP-AKA: Unrecognized username '%s'",
			   username);
		os_free(username);
		data->notification = EAP_SIM_GENERAL_FAILURE_BEFORE_AUTH;
		eap_aka_state(data, NOTIFICATION);
		return;
	}

	eap_aka_fullauth(sm, data);
}