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
struct eap_sim_data {scalar_t__ use_result_ind; } ;

/* Variables and functions */
 int /*<<< orphan*/  CLEAR_EAP_ID ; 
 int /*<<< orphan*/  eap_sim_clear_identities (struct eap_sm*,struct eap_sim_data*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  eap_sim_clear_keys (struct eap_sim_data*,int) ; 

__attribute__((used)) static void eap_sim_deinit_for_reauth(struct eap_sm *sm, void *priv)
{
	struct eap_sim_data *data = priv;
	eap_sim_clear_identities(sm, data, CLEAR_EAP_ID);
	data->use_result_ind = 0;
	eap_sim_clear_keys(data, 1);
}