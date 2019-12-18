#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct wpa_sm_ctx {int /*<<< orphan*/  msg_ctx; } ;
struct wpa_sm {int renew_snonce; int dot11RSNAConfigPMKLifetime; int dot11RSNAConfigPMKReauthThreshold; int dot11RSNAConfigSATimeout; struct wpa_sm_ctx* ctx; int /*<<< orphan*/ * pmksa; int /*<<< orphan*/  pmksa_candidates; } ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_ERROR ; 
 int /*<<< orphan*/  dl_list_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  os_free (struct wpa_sm*) ; 
 struct wpa_sm* os_zalloc (int) ; 
 int /*<<< orphan*/ * pmksa_cache_init (int /*<<< orphan*/ ,struct wpa_sm*,struct wpa_sm*) ; 
 int /*<<< orphan*/  wpa_msg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  wpa_sm_pmksa_free_cb ; 

struct wpa_sm * wpa_sm_init(struct wpa_sm_ctx *ctx)
{
	struct wpa_sm *sm;

	sm = os_zalloc(sizeof(*sm));
	if (sm == NULL)
		return NULL;
	dl_list_init(&sm->pmksa_candidates);
	sm->renew_snonce = 1;
	sm->ctx = ctx;

	sm->dot11RSNAConfigPMKLifetime = 43200;
	sm->dot11RSNAConfigPMKReauthThreshold = 70;
	sm->dot11RSNAConfigSATimeout = 60;

	sm->pmksa = pmksa_cache_init(wpa_sm_pmksa_free_cb, sm, sm);
	if (sm->pmksa == NULL) {
		wpa_msg(sm->ctx->msg_ctx, MSG_ERROR,
			"RSN: PMKSA cache initialization failed");
		os_free(sm);
		return NULL;
	}

	return sm;
}