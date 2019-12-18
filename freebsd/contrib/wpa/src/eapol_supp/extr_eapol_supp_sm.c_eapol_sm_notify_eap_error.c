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
struct TYPE_2__ {int /*<<< orphan*/  ctx; int /*<<< orphan*/  (* eap_error_cb ) (int /*<<< orphan*/ ,int) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void eapol_sm_notify_eap_error(void *ctx, int error_code)
{
	struct eapol_sm *sm = ctx;

	if (sm->ctx->eap_error_cb)
		sm->ctx->eap_error_cb(sm->ctx->ctx, error_code);
}