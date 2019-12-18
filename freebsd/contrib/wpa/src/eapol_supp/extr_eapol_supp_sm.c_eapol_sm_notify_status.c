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
struct TYPE_2__ {int /*<<< orphan*/  ctx; int /*<<< orphan*/  (* status_cb ) (int /*<<< orphan*/ ,char const*,char const*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,char const*,char const*) ; 

__attribute__((used)) static void eapol_sm_notify_status(void *ctx, const char *status,
				   const char *parameter)
{
	struct eapol_sm *sm = ctx;

	if (sm->ctx->status_cb)
		sm->ctx->status_cb(sm->ctx->ctx, status, parameter);
}