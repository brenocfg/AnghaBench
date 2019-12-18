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
struct hostapd_config {size_t num_bss; struct hostapd_bss_config** bss; struct hostapd_bss_config* last_bss; int /*<<< orphan*/ * driver; } ;
struct hostapd_bss_config {int dummy; } ;
typedef  int /*<<< orphan*/  buf ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_ERROR ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 scalar_t__ fgets (char*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char const*,char*) ; 
 scalar_t__ hostapd_config_check (struct hostapd_config*,int) ; 
 struct hostapd_config* hostapd_config_defaults () ; 
 scalar_t__ hostapd_config_fill (struct hostapd_config*,struct hostapd_bss_config*,char*,char*,int) ; 
 int /*<<< orphan*/  hostapd_config_free (struct hostapd_config*) ; 
 int /*<<< orphan*/  hostapd_set_security_params (struct hostapd_bss_config*,int) ; 
 char* os_strchr (char*,char) ; 
 int /*<<< orphan*/ ** wpa_drivers ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,...) ; 

struct hostapd_config * hostapd_config_read(const char *fname)
{
	struct hostapd_config *conf;
	FILE *f;
	char buf[4096], *pos;
	int line = 0;
	int errors = 0;
	size_t i;

	f = fopen(fname, "r");
	if (f == NULL) {
		wpa_printf(MSG_ERROR, "Could not open configuration file '%s' "
			   "for reading.", fname);
		return NULL;
	}

	conf = hostapd_config_defaults();
	if (conf == NULL) {
		fclose(f);
		return NULL;
	}

	/* set default driver based on configuration */
	conf->driver = wpa_drivers[0];
	if (conf->driver == NULL) {
		wpa_printf(MSG_ERROR, "No driver wrappers registered!");
		hostapd_config_free(conf);
		fclose(f);
		return NULL;
	}

	conf->last_bss = conf->bss[0];

	while (fgets(buf, sizeof(buf), f)) {
		struct hostapd_bss_config *bss;

		bss = conf->last_bss;
		line++;

		if (buf[0] == '#')
			continue;
		pos = buf;
		while (*pos != '\0') {
			if (*pos == '\n') {
				*pos = '\0';
				break;
			}
			pos++;
		}
		if (buf[0] == '\0')
			continue;

		pos = os_strchr(buf, '=');
		if (pos == NULL) {
			wpa_printf(MSG_ERROR, "Line %d: invalid line '%s'",
				   line, buf);
			errors++;
			continue;
		}
		*pos = '\0';
		pos++;
		errors += hostapd_config_fill(conf, bss, buf, pos, line);
	}

	fclose(f);

	for (i = 0; i < conf->num_bss; i++)
		hostapd_set_security_params(conf->bss[i], 1);

	if (hostapd_config_check(conf, 1))
		errors++;

#ifndef WPA_IGNORE_CONFIG_ERRORS
	if (errors) {
		wpa_printf(MSG_ERROR, "%d errors found in configuration file "
			   "'%s'", errors, fname);
		hostapd_config_free(conf);
		conf = NULL;
	}
#endif /* WPA_IGNORE_CONFIG_ERRORS */

	return conf;
}