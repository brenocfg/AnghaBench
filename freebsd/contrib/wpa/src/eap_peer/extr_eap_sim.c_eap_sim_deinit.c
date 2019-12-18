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
struct eap_sim_data {struct eap_sim_data* last_eap_identity; struct eap_sim_data* reauth_id; struct eap_sim_data* pseudonym; struct eap_sim_data* ver_list; } ;

/* Variables and functions */
 int /*<<< orphan*/  eap_sim_clear_keys (struct eap_sim_data*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  os_free (struct eap_sim_data*) ; 

__attribute__((used)) static void eap_sim_deinit(struct eap_sm *sm, void *priv)
{
	struct eap_sim_data *data = priv;
	if (data) {
		os_free(data->ver_list);
		os_free(data->pseudonym);
		os_free(data->reauth_id);
		os_free(data->last_eap_identity);
		eap_sim_clear_keys(data, 0);
		os_free(data);
	}
}