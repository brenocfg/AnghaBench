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
struct eap_sm {int /*<<< orphan*/  peap_done; } ;
struct eap_peap_data {int resuming; int reauth; scalar_t__ phase2_eap_started; scalar_t__ phase2_eap_success; scalar_t__ phase2_success; scalar_t__ phase2_priv; TYPE_1__* phase2_method; int /*<<< orphan*/  ssl; struct eap_peap_data* session_id; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* init_for_reauth ) (struct eap_sm*,scalar_t__) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  eap_peap_free_key (struct eap_peap_data*) ; 
 scalar_t__ eap_peer_tls_reauth_init (struct eap_sm*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  os_free (struct eap_peap_data*) ; 
 int /*<<< orphan*/  stub1 (struct eap_sm*,scalar_t__) ; 

__attribute__((used)) static void * eap_peap_init_for_reauth(struct eap_sm *sm, void *priv)
{
	struct eap_peap_data *data = priv;
	eap_peap_free_key(data);
	os_free(data->session_id);
	data->session_id = NULL;
	if (eap_peer_tls_reauth_init(sm, &data->ssl)) {
		os_free(data);
		return NULL;
	}
	if (data->phase2_priv && data->phase2_method &&
	    data->phase2_method->init_for_reauth)
		data->phase2_method->init_for_reauth(sm, data->phase2_priv);
	data->phase2_success = 0;
	data->phase2_eap_success = 0;
	data->phase2_eap_started = 0;
	data->resuming = 1;
	data->reauth = 1;
	sm->peap_done = FALSE;
	return priv;
}