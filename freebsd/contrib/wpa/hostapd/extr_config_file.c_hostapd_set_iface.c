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
struct hostapd_config {size_t num_bss; int /*<<< orphan*/ * bss; } ;
struct hostapd_bss_config {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_ERROR ; 
 int /*<<< orphan*/  MSG_INFO ; 
 scalar_t__ hostapd_config_check (struct hostapd_config*,int /*<<< orphan*/ ) ; 
 int hostapd_config_fill (struct hostapd_config*,struct hostapd_bss_config*,char const*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hostapd_set_security_params (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,...) ; 

int hostapd_set_iface(struct hostapd_config *conf,
		      struct hostapd_bss_config *bss, const char *field,
		      char *value)
{
	int errors;
	size_t i;

	errors = hostapd_config_fill(conf, bss, field, value, 0);
	if (errors) {
		wpa_printf(MSG_INFO, "Failed to set configuration field '%s' "
			   "to value '%s'", field, value);
		return -1;
	}

	for (i = 0; i < conf->num_bss; i++)
		hostapd_set_security_params(conf->bss[i], 0);

	if (hostapd_config_check(conf, 0)) {
		wpa_printf(MSG_ERROR, "Configuration check failed");
		return -1;
	}

	return 0;
}