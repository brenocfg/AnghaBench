#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct eap_sm {int init_phase2; int /*<<< orphan*/ * peer_challenge; int /*<<< orphan*/ * auth_challenge; } ;
struct eap_fast_data {int /*<<< orphan*/ * phase2_priv; TYPE_2__* phase2_method; TYPE_1__* key_block_p; } ;
struct TYPE_4__ {int /*<<< orphan*/ * (* init ) (struct eap_sm*) ;int /*<<< orphan*/  (* reset ) (struct eap_sm*,int /*<<< orphan*/ *) ;} ;
struct TYPE_3__ {int /*<<< orphan*/ * client_challenge; int /*<<< orphan*/ * server_challenge; } ;
typedef  int /*<<< orphan*/  EapType ;

/* Variables and functions */
 int /*<<< orphan*/  EAP_VENDOR_IETF ; 
 TYPE_2__* eap_server_get_eap_method (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct eap_sm*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * stub2 (struct eap_sm*) ; 

__attribute__((used)) static int eap_fast_phase2_init(struct eap_sm *sm, struct eap_fast_data *data,
				EapType eap_type)
{
	if (data->phase2_priv && data->phase2_method) {
		data->phase2_method->reset(sm, data->phase2_priv);
		data->phase2_method = NULL;
		data->phase2_priv = NULL;
	}
	data->phase2_method = eap_server_get_eap_method(EAP_VENDOR_IETF,
							eap_type);
	if (!data->phase2_method)
		return -1;

	if (data->key_block_p) {
		sm->auth_challenge = data->key_block_p->server_challenge;
		sm->peer_challenge = data->key_block_p->client_challenge;
	}
	sm->init_phase2 = 1;
	data->phase2_priv = data->phase2_method->init(sm);
	sm->init_phase2 = 0;
	sm->auth_challenge = NULL;
	sm->peer_challenge = NULL;

	return data->phase2_priv == NULL ? -1 : 0;
}