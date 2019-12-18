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
struct wpa_group {int /*<<< orphan*/  GInit; int /*<<< orphan*/  GTK_len; } ;
struct TYPE_2__ {int /*<<< orphan*/  wpa_group; } ;
struct wpa_authenticator {TYPE_1__ conf; struct wpa_group* group; } ;
struct wpa_auth_config {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  MSG_ERROR ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  os_memcpy (TYPE_1__*,struct wpa_auth_config*,int) ; 
 scalar_t__ wpa_auth_gen_wpa_ie (struct wpa_authenticator*) ; 
 int /*<<< orphan*/  wpa_cipher_key_len (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wpa_group_sm_step (struct wpa_authenticator*,struct wpa_group*) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*) ; 

int wpa_reconfig(struct wpa_authenticator *wpa_auth,
		 struct wpa_auth_config *conf)
{
	struct wpa_group *group;
	if (wpa_auth == NULL)
		return 0;

	os_memcpy(&wpa_auth->conf, conf, sizeof(*conf));
	if (wpa_auth_gen_wpa_ie(wpa_auth)) {
		wpa_printf(MSG_ERROR, "Could not generate WPA IE.");
		return -1;
	}

	/*
	 * Reinitialize GTK to make sure it is suitable for the new
	 * configuration.
	 */
	group = wpa_auth->group;
	group->GTK_len = wpa_cipher_key_len(wpa_auth->conf.wpa_group);
	group->GInit = TRUE;
	wpa_group_sm_step(wpa_auth, group);
	group->GInit = FALSE;
	wpa_group_sm_step(wpa_auth, group);

	return 0;
}