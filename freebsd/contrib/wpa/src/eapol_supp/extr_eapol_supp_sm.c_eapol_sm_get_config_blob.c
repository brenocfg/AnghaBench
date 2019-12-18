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
struct TYPE_2__ {int /*<<< orphan*/  ctx; struct wpa_config_blob const* (* get_config_blob ) (int /*<<< orphan*/ ,char const*) ;} ;

/* Variables and functions */
 struct wpa_config_blob const* stub1 (int /*<<< orphan*/ ,char const*) ; 

__attribute__((used)) static const struct wpa_config_blob *
eapol_sm_get_config_blob(void *ctx, const char *name)
{
#ifndef CONFIG_NO_CONFIG_BLOBS
	struct eapol_sm *sm = ctx;
	if (sm && sm->ctx && sm->ctx->get_config_blob)
		return sm->ctx->get_config_blob(sm->ctx->ctx, name);
	else
		return NULL;
#else /* CONFIG_NO_CONFIG_BLOBS */
	return NULL;
#endif /* CONFIG_NO_CONFIG_BLOBS */
}