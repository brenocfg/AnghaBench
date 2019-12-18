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
struct eap_sim_db_data {int dummy; } ;
typedef  enum eap_sim_db_method { ____Placeholder_eap_sim_db_method } eap_sim_db_method ;

/* Variables and functions */
 char EAP_AKA_PRIME_PSEUDONYM_PREFIX ; 
 char EAP_AKA_PSEUDONYM_PREFIX ; 
#define  EAP_SIM_DB_AKA 130 
#define  EAP_SIM_DB_AKA_PRIME 129 
#define  EAP_SIM_DB_SIM 128 
 char EAP_SIM_PSEUDONYM_PREFIX ; 
 char EAP_SIM_REAUTH_ID_PREFIX ; 
 char* eap_sim_db_get_next (struct eap_sim_db_data*,char) ; 

char * eap_sim_db_get_next_pseudonym(struct eap_sim_db_data *data,
				     enum eap_sim_db_method method)
{
	char prefix = EAP_SIM_REAUTH_ID_PREFIX;

	switch (method) {
	case EAP_SIM_DB_SIM:
		prefix = EAP_SIM_PSEUDONYM_PREFIX;
		break;
	case EAP_SIM_DB_AKA:
		prefix = EAP_AKA_PSEUDONYM_PREFIX;
		break;
	case EAP_SIM_DB_AKA_PRIME:
		prefix = EAP_AKA_PRIME_PSEUDONYM_PREFIX;
		break;
	}

	return eap_sim_db_get_next(data, prefix);
}