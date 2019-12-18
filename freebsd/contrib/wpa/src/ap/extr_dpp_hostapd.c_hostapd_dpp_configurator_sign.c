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
struct hostapd_data {int /*<<< orphan*/  msg_ctx; TYPE_1__* iface; } ;
struct dpp_authentication {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  dpp; } ;
struct TYPE_3__ {TYPE_2__* interfaces; } ;

/* Variables and functions */
 int /*<<< orphan*/  dpp_auth_deinit (struct dpp_authentication*) ; 
 scalar_t__ dpp_configurator_own_config (struct dpp_authentication*,char*,int) ; 
 scalar_t__ dpp_set_configurator (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct dpp_authentication*,char const*) ; 
 char* get_param (char const*,char*) ; 
 int /*<<< orphan*/  hostapd_dpp_handle_config_obj (struct hostapd_data*,struct dpp_authentication*) ; 
 int /*<<< orphan*/  hostapd_dpp_set_testing_options (struct hostapd_data*,struct dpp_authentication*) ; 
 int /*<<< orphan*/  os_free (char*) ; 
 struct dpp_authentication* os_zalloc (int) ; 

int hostapd_dpp_configurator_sign(struct hostapd_data *hapd, const char *cmd)
{
	struct dpp_authentication *auth;
	int ret = -1;
	char *curve = NULL;

	auth = os_zalloc(sizeof(*auth));
	if (!auth)
		return -1;

	curve = get_param(cmd, " curve=");
	hostapd_dpp_set_testing_options(hapd, auth);
	if (dpp_set_configurator(hapd->iface->interfaces->dpp, hapd->msg_ctx,
				 auth, cmd) == 0 &&
	    dpp_configurator_own_config(auth, curve, 1) == 0) {
		hostapd_dpp_handle_config_obj(hapd, auth);
		ret = 0;
	}

	dpp_auth_deinit(auth);
	os_free(curve);

	return ret;
}