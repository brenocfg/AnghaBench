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
struct eap_aka_data {struct eap_aka_data* network_name; int /*<<< orphan*/  id_msgs; struct eap_aka_data* last_eap_identity; struct eap_aka_data* reauth_id; struct eap_aka_data* pseudonym; } ;

/* Variables and functions */
 int /*<<< orphan*/  eap_aka_clear_keys (struct eap_aka_data*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  os_free (struct eap_aka_data*) ; 
 int /*<<< orphan*/  wpabuf_free (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void eap_aka_deinit(struct eap_sm *sm, void *priv)
{
	struct eap_aka_data *data = priv;
	if (data) {
		os_free(data->pseudonym);
		os_free(data->reauth_id);
		os_free(data->last_eap_identity);
		wpabuf_free(data->id_msgs);
		os_free(data->network_name);
		eap_aka_clear_keys(data, 0);
		os_free(data);
	}
}