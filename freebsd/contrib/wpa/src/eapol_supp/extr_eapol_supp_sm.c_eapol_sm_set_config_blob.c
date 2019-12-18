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
struct wpa_config_blob {int dummy; } ;
struct eapol_sm {TYPE_1__* ctx; } ;
struct TYPE_2__ {int /*<<< orphan*/  ctx; int /*<<< orphan*/  (* set_config_blob ) (int /*<<< orphan*/ ,struct wpa_config_blob*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,struct wpa_config_blob*) ; 

__attribute__((used)) static void eapol_sm_set_config_blob(void *ctx, struct wpa_config_blob *blob)
{
#ifndef CONFIG_NO_CONFIG_BLOBS
	struct eapol_sm *sm = ctx;
	if (sm && sm->ctx && sm->ctx->set_config_blob)
		sm->ctx->set_config_blob(sm->ctx->ctx, blob);
#endif /* CONFIG_NO_CONFIG_BLOBS */
}