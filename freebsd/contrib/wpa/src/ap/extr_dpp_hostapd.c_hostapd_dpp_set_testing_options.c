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
struct hostapd_data {int /*<<< orphan*/  dpp_ignore_netaccesskey_mismatch; scalar_t__ dpp_groups_override; scalar_t__ dpp_discovery_override; scalar_t__ dpp_config_obj_override; } ;
struct dpp_authentication {int /*<<< orphan*/  ignore_netaccesskey_mismatch; void* groups_override; void* discovery_override; void* config_obj_override; } ;

/* Variables and functions */
 void* os_strdup (scalar_t__) ; 

__attribute__((used)) static void hostapd_dpp_set_testing_options(struct hostapd_data *hapd,
					    struct dpp_authentication *auth)
{
#ifdef CONFIG_TESTING_OPTIONS
	if (hapd->dpp_config_obj_override)
		auth->config_obj_override =
			os_strdup(hapd->dpp_config_obj_override);
	if (hapd->dpp_discovery_override)
		auth->discovery_override =
			os_strdup(hapd->dpp_discovery_override);
	if (hapd->dpp_groups_override)
		auth->groups_override = os_strdup(hapd->dpp_groups_override);
	auth->ignore_netaccesskey_mismatch =
		hapd->dpp_ignore_netaccesskey_mismatch;
#endif /* CONFIG_TESTING_OPTIONS */
}