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
struct eap_sm {int dummy; } ;
struct eap_peap_data {scalar_t__ crypto_binding_used; int /*<<< orphan*/ * pending_resp; int /*<<< orphan*/ * pending_phase2_req; scalar_t__ phase2_priv; TYPE_1__* phase2_method; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* deinit_for_reauth ) (struct eap_sm*,scalar_t__) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (struct eap_sm*,scalar_t__) ; 
 int /*<<< orphan*/  wpabuf_clear_free (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void eap_peap_deinit_for_reauth(struct eap_sm *sm, void *priv)
{
	struct eap_peap_data *data = priv;

	if (data->phase2_priv && data->phase2_method &&
	    data->phase2_method->deinit_for_reauth)
		data->phase2_method->deinit_for_reauth(sm, data->phase2_priv);
	wpabuf_clear_free(data->pending_phase2_req);
	data->pending_phase2_req = NULL;
	wpabuf_clear_free(data->pending_resp);
	data->pending_resp = NULL;
	data->crypto_binding_used = 0;
}