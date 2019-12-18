#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct eap_sm {int init_phase2; int /*<<< orphan*/ * peer_challenge; int /*<<< orphan*/ * auth_challenge; } ;
struct TYPE_4__ {int /*<<< orphan*/  method; int /*<<< orphan*/  vendor; } ;
struct eap_fast_data {int /*<<< orphan*/ * phase2_priv; TYPE_3__* phase2_method; TYPE_2__* key_block_p; TYPE_1__ phase2_type; } ;
struct TYPE_6__ {int /*<<< orphan*/ * (* init ) (struct eap_sm*) ;} ;
struct TYPE_5__ {int /*<<< orphan*/ * client_challenge; int /*<<< orphan*/ * server_challenge; } ;

/* Variables and functions */
 TYPE_3__* eap_peer_get_eap_method (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * stub1 (struct eap_sm*) ; 

__attribute__((used)) static int eap_fast_init_phase2_method(struct eap_sm *sm,
				       struct eap_fast_data *data)
{
	data->phase2_method =
		eap_peer_get_eap_method(data->phase2_type.vendor,
					data->phase2_type.method);
	if (data->phase2_method == NULL)
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