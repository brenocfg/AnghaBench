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
struct eap_sm {int /*<<< orphan*/  eapol_ctx; TYPE_1__* eapol_cb; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* set_config_blob ) (int /*<<< orphan*/ ,struct wpa_config_blob*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,struct wpa_config_blob*) ; 

void eap_set_config_blob(struct eap_sm *sm, struct wpa_config_blob *blob)
{
#ifndef CONFIG_NO_CONFIG_BLOBS
	sm->eapol_cb->set_config_blob(sm->eapol_ctx, blob);
#endif /* CONFIG_NO_CONFIG_BLOBS */
}