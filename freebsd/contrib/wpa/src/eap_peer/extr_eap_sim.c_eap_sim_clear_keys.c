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
struct eap_sim_data {int /*<<< orphan*/  emsk; int /*<<< orphan*/  msk; int /*<<< orphan*/  sres; int /*<<< orphan*/  kc; int /*<<< orphan*/  k_encr; int /*<<< orphan*/  k_aut; int /*<<< orphan*/  mk; } ;

/* Variables and functions */
 int EAP_EMSK_LEN ; 
 int EAP_SIM_KC_LEN ; 
 int EAP_SIM_KEYING_DATA_LEN ; 
 int EAP_SIM_K_AUT_LEN ; 
 int EAP_SIM_K_ENCR_LEN ; 
 int EAP_SIM_MK_LEN ; 
 int EAP_SIM_SRES_LEN ; 
 int /*<<< orphan*/  os_memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void eap_sim_clear_keys(struct eap_sim_data *data, int reauth)
{
	if (!reauth) {
		os_memset(data->mk, 0, EAP_SIM_MK_LEN);
		os_memset(data->k_aut, 0, EAP_SIM_K_AUT_LEN);
		os_memset(data->k_encr, 0, EAP_SIM_K_ENCR_LEN);
	}
	os_memset(data->kc, 0, 3 * EAP_SIM_KC_LEN);
	os_memset(data->sres, 0, 3 * EAP_SIM_SRES_LEN);
	os_memset(data->msk, 0, EAP_SIM_KEYING_DATA_LEN);
	os_memset(data->emsk, 0, EAP_EMSK_LEN);
}