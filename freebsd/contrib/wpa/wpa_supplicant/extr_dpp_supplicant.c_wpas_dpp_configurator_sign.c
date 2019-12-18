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
struct wpa_supplicant {int /*<<< orphan*/  dpp; } ;
struct dpp_authentication {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  dpp_auth_deinit (struct dpp_authentication*) ; 
 scalar_t__ dpp_configurator_own_config (struct dpp_authentication*,char*,int /*<<< orphan*/ ) ; 
 scalar_t__ dpp_set_configurator (int /*<<< orphan*/ ,struct wpa_supplicant*,struct dpp_authentication*,char const*) ; 
 char* get_param (char const*,char*) ; 
 int /*<<< orphan*/  os_free (char*) ; 
 struct dpp_authentication* os_zalloc (int) ; 
 int wpas_dpp_handle_config_obj (struct wpa_supplicant*,struct dpp_authentication*) ; 
 int /*<<< orphan*/  wpas_dpp_set_testing_options (struct wpa_supplicant*,struct dpp_authentication*) ; 

int wpas_dpp_configurator_sign(struct wpa_supplicant *wpa_s, const char *cmd)
{
	struct dpp_authentication *auth;
	int ret = -1;
	char *curve = NULL;

	auth = os_zalloc(sizeof(*auth));
	if (!auth)
		return -1;

	curve = get_param(cmd, " curve=");
	wpas_dpp_set_testing_options(wpa_s, auth);
	if (dpp_set_configurator(wpa_s->dpp, wpa_s, auth, cmd) == 0 &&
	    dpp_configurator_own_config(auth, curve, 0) == 0)
		ret = wpas_dpp_handle_config_obj(wpa_s, auth);

	dpp_auth_deinit(auth);
	os_free(curve);

	return ret;
}