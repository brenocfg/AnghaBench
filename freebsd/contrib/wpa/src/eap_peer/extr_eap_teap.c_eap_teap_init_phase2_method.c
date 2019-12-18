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
struct TYPE_3__ {int /*<<< orphan*/  method; int /*<<< orphan*/  vendor; } ;
struct eap_teap_data {int /*<<< orphan*/ * phase2_priv; TYPE_2__* phase2_method; TYPE_1__ phase2_type; scalar_t__ inner_method_done; } ;
struct eap_sm {int init_phase2; } ;
struct TYPE_4__ {int /*<<< orphan*/ * (* init ) (struct eap_sm*) ;} ;

/* Variables and functions */
 TYPE_2__* eap_peer_get_eap_method (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * stub1 (struct eap_sm*) ; 

__attribute__((used)) static int eap_teap_init_phase2_method(struct eap_sm *sm,
				       struct eap_teap_data *data)
{
	data->inner_method_done = 0;
	data->phase2_method =
		eap_peer_get_eap_method(data->phase2_type.vendor,
					data->phase2_type.method);
	if (!data->phase2_method)
		return -1;

	sm->init_phase2 = 1;
	data->phase2_priv = data->phase2_method->init(sm);
	sm->init_phase2 = 0;

	return data->phase2_priv == NULL ? -1 : 0;
}