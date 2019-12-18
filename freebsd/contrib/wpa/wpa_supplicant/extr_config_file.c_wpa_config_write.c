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
struct wpa_ssid {scalar_t__ key_mgmt; int /*<<< orphan*/  passphrase; int /*<<< orphan*/  psk_set; scalar_t__ temporary; struct wpa_ssid* next; } ;
struct wpa_cred {scalar_t__ temporary; struct wpa_cred* next; } ;
struct wpa_config_blob {struct wpa_config_blob* next; } ;
struct wpa_config {struct wpa_config_blob* blobs; struct wpa_ssid* ssid; struct wpa_cred* cred; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_DEBUG ; 
 int S_IRGRP ; 
 int S_IRUSR ; 
 int S_IWGRP ; 
 int S_IWUSR ; 
 scalar_t__ WPA_KEY_MGMT_WPS ; 
 int chmod (char*,int) ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char const*,char*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  os_fdatasync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  os_free (char*) ; 
 char* os_malloc (int) ; 
 int /*<<< orphan*/  os_snprintf (char*,int,char*,char const*) ; 
 int os_strlen (char const*) ; 
 scalar_t__ rename (char*,char const*) ; 
 int wpa_config_write_blob (int /*<<< orphan*/ *,struct wpa_config_blob*) ; 
 int /*<<< orphan*/  wpa_config_write_cred (int /*<<< orphan*/ *,struct wpa_cred*) ; 
 int /*<<< orphan*/  wpa_config_write_global (int /*<<< orphan*/ *,struct wpa_config*) ; 
 int /*<<< orphan*/  wpa_config_write_network (int /*<<< orphan*/ *,struct wpa_ssid*) ; 
 scalar_t__ wpa_key_mgmt_wpa_psk (scalar_t__) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,char const*,...) ; 

int wpa_config_write(const char *name, struct wpa_config *config)
{
#ifndef CONFIG_NO_CONFIG_WRITE
	FILE *f;
	struct wpa_ssid *ssid;
	struct wpa_cred *cred;
#ifndef CONFIG_NO_CONFIG_BLOBS
	struct wpa_config_blob *blob;
#endif /* CONFIG_NO_CONFIG_BLOBS */
	int ret = 0;
	const char *orig_name = name;
	int tmp_len = os_strlen(name) + 5; /* allow space for .tmp suffix */
	char *tmp_name = os_malloc(tmp_len);

	if (tmp_name) {
		os_snprintf(tmp_name, tmp_len, "%s.tmp", name);
		name = tmp_name;
	}

	wpa_printf(MSG_DEBUG, "Writing configuration file '%s'", name);

	f = fopen(name, "w");
	if (f == NULL) {
		wpa_printf(MSG_DEBUG, "Failed to open '%s' for writing", name);
		os_free(tmp_name);
		return -1;
	}

	wpa_config_write_global(f, config);

	for (cred = config->cred; cred; cred = cred->next) {
		if (cred->temporary)
			continue;
		fprintf(f, "\ncred={\n");
		wpa_config_write_cred(f, cred);
		fprintf(f, "}\n");
	}

	for (ssid = config->ssid; ssid; ssid = ssid->next) {
		if (ssid->key_mgmt == WPA_KEY_MGMT_WPS || ssid->temporary)
			continue; /* do not save temporary networks */
		if (wpa_key_mgmt_wpa_psk(ssid->key_mgmt) && !ssid->psk_set &&
		    !ssid->passphrase)
			continue; /* do not save invalid network */
		fprintf(f, "\nnetwork={\n");
		wpa_config_write_network(f, ssid);
		fprintf(f, "}\n");
	}

#ifndef CONFIG_NO_CONFIG_BLOBS
	for (blob = config->blobs; blob; blob = blob->next) {
		ret = wpa_config_write_blob(f, blob);
		if (ret)
			break;
	}
#endif /* CONFIG_NO_CONFIG_BLOBS */

	os_fdatasync(f);

	fclose(f);

	if (tmp_name) {
		int chmod_ret = 0;

#ifdef ANDROID
		chmod_ret = chmod(tmp_name,
				  S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP);
#endif /* ANDROID */
		if (chmod_ret != 0 || rename(tmp_name, orig_name) != 0)
			ret = -1;

		os_free(tmp_name);
	}

	wpa_printf(MSG_DEBUG, "Configuration file '%s' written %ssuccessfully",
		   orig_name, ret ? "un" : "");
	return ret;
#else /* CONFIG_NO_CONFIG_WRITE */
	return -1;
#endif /* CONFIG_NO_CONFIG_WRITE */
}