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
struct eap_sm {int /*<<< orphan*/  eap_sim_db_priv; } ;
struct eap_aka_data {scalar_t__ eap_method; TYPE_1__* reauth; int /*<<< orphan*/  mk; int /*<<< orphan*/  k_re; int /*<<< orphan*/  k_aut; int /*<<< orphan*/  k_encr; int /*<<< orphan*/  counter; int /*<<< orphan*/  permanent; } ;
struct TYPE_2__ {int /*<<< orphan*/  mk; int /*<<< orphan*/  k_re; int /*<<< orphan*/  k_aut; int /*<<< orphan*/  k_encr; int /*<<< orphan*/  counter; int /*<<< orphan*/  permanent; } ;

/* Variables and functions */
 int /*<<< orphan*/  EAP_AKA_PRIME_K_AUT_LEN ; 
 int /*<<< orphan*/  EAP_AKA_PRIME_K_RE_LEN ; 
 char const EAP_AKA_PRIME_REAUTH_ID_PREFIX ; 
 char const EAP_AKA_REAUTH_ID_PREFIX ; 
 int /*<<< orphan*/  EAP_SIM_K_ENCR_LEN ; 
 int /*<<< orphan*/  EAP_SIM_MK_LEN ; 
 scalar_t__ EAP_TYPE_AKA ; 
 scalar_t__ EAP_TYPE_AKA_PRIME ; 
 int /*<<< orphan*/  MSG_DEBUG ; 
 int /*<<< orphan*/  REAUTH ; 
 int /*<<< orphan*/  eap_aka_state (struct eap_aka_data*,int /*<<< orphan*/ ) ; 
 TYPE_1__* eap_sim_db_get_reauth_entry (int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  os_memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  os_strlcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,...) ; 

__attribute__((used)) static int eap_aka_check_identity_reauth(struct eap_sm *sm,
					 struct eap_aka_data *data,
					 const char *username)
{
	if (data->eap_method == EAP_TYPE_AKA_PRIME &&
	    username[0] != EAP_AKA_PRIME_REAUTH_ID_PREFIX)
		return 0;
	if (data->eap_method == EAP_TYPE_AKA &&
	    username[0] != EAP_AKA_REAUTH_ID_PREFIX)
		return 0;

	wpa_printf(MSG_DEBUG, "EAP-AKA: Reauth username '%s'", username);
	data->reauth = eap_sim_db_get_reauth_entry(sm->eap_sim_db_priv,
						   username);
	if (data->reauth == NULL) {
		wpa_printf(MSG_DEBUG, "EAP-AKA: Unknown reauth identity - "
			   "request full auth identity");
		/* Remain in IDENTITY state for another round */
		return 0;
	}

	wpa_printf(MSG_DEBUG, "EAP-AKA: Using fast re-authentication");
	os_strlcpy(data->permanent, data->reauth->permanent,
		   sizeof(data->permanent));
	data->counter = data->reauth->counter;
	if (data->eap_method == EAP_TYPE_AKA_PRIME) {
		os_memcpy(data->k_encr, data->reauth->k_encr,
			  EAP_SIM_K_ENCR_LEN);
		os_memcpy(data->k_aut, data->reauth->k_aut,
			  EAP_AKA_PRIME_K_AUT_LEN);
		os_memcpy(data->k_re, data->reauth->k_re,
			  EAP_AKA_PRIME_K_RE_LEN);
	} else {
		os_memcpy(data->mk, data->reauth->mk, EAP_SIM_MK_LEN);
	}

	eap_aka_state(data, REAUTH);
	return 1;
}