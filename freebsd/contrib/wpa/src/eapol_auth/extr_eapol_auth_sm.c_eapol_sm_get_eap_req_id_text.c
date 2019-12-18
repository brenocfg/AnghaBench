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
struct eapol_state_machine {TYPE_2__* eapol; } ;
struct TYPE_3__ {size_t eap_req_id_text_len; char const* eap_req_id_text; } ;
struct TYPE_4__ {TYPE_1__ conf; } ;

/* Variables and functions */

__attribute__((used)) static const char * eapol_sm_get_eap_req_id_text(void *ctx, size_t *len)
{
	struct eapol_state_machine *sm = ctx;
	*len = sm->eapol->conf.eap_req_id_text_len;
	return sm->eapol->conf.eap_req_id_text;
}