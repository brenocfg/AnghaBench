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
struct eap_ttls_data {int /*<<< orphan*/ * phase2_priv; TYPE_1__* phase2_method; } ;
struct eap_sm {int init_phase2; } ;
struct TYPE_2__ {int /*<<< orphan*/ * (* init ) (struct eap_sm*) ;int /*<<< orphan*/  (* reset ) (struct eap_sm*,int /*<<< orphan*/ *) ;} ;
typedef  int /*<<< orphan*/  EapType ;

/* Variables and functions */
 int /*<<< orphan*/  EAP_VENDOR_IETF ; 
 TYPE_1__* eap_server_get_eap_method (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct eap_sm*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * stub2 (struct eap_sm*) ; 

__attribute__((used)) static int eap_ttls_phase2_eap_init(struct eap_sm *sm,
				    struct eap_ttls_data *data,
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

	sm->init_phase2 = 1;
	data->phase2_priv = data->phase2_method->init(sm);
	sm->init_phase2 = 0;
	return data->phase2_priv == NULL ? -1 : 0;
}