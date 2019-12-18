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
struct eapol_sm {TYPE_1__* ctx; } ;
typedef  enum wpa_ctrl_req_type { ____Placeholder_wpa_ctrl_req_type } wpa_ctrl_req_type ;
struct TYPE_2__ {int /*<<< orphan*/  ctx; int /*<<< orphan*/  (* eap_param_needed ) (int /*<<< orphan*/ ,int,char const*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_DEBUG ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int,char const*) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void eapol_sm_eap_param_needed(void *ctx, enum wpa_ctrl_req_type field,
				      const char *txt)
{
	struct eapol_sm *sm = ctx;
	wpa_printf(MSG_DEBUG, "EAPOL: EAP parameter needed");
	if (sm->ctx->eap_param_needed)
		sm->ctx->eap_param_needed(sm->ctx->ctx, field, txt);
}