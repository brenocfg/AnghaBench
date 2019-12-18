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
struct wpa_ssid {struct wpa_ssid* next; } ;
struct wpa_cred {struct wpa_cred* next; } ;
struct wpa_config {struct wpa_cred* cred; struct wpa_ssid* ssid; } ;
typedef  int /*<<< orphan*/  buf ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_DEBUG ; 
 int /*<<< orphan*/  MSG_ERROR ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char const*,char*) ; 
 int /*<<< orphan*/  os_free (struct wpa_config*) ; 
 scalar_t__ os_strcmp (char*,char*) ; 
 scalar_t__ os_strncmp (char*,char*,int) ; 
 int /*<<< orphan*/  strerror (int /*<<< orphan*/ ) ; 
 scalar_t__ wpa_config_add_prio_network (struct wpa_config*,struct wpa_ssid*) ; 
 struct wpa_config* wpa_config_alloc_empty (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wpa_config_debug_dump_networks (struct wpa_config*) ; 
 int /*<<< orphan*/  wpa_config_free (struct wpa_config*) ; 
 scalar_t__ wpa_config_get_line (char*,int,int /*<<< orphan*/ *,int*,char**) ; 
 scalar_t__ wpa_config_process_blob (struct wpa_config*,int /*<<< orphan*/ *,int*,char*) ; 
 scalar_t__ wpa_config_process_global (struct wpa_config*,char*,int) ; 
 struct wpa_cred* wpa_config_read_cred (int /*<<< orphan*/ *,int*,int /*<<< orphan*/ ) ; 
 struct wpa_ssid* wpa_config_read_network (int /*<<< orphan*/ *,int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,...) ; 

struct wpa_config * wpa_config_read(const char *name, struct wpa_config *cfgp)
{
	FILE *f;
	char buf[512], *pos;
	int errors = 0, line = 0;
	struct wpa_ssid *ssid, *tail, *head;
	struct wpa_cred *cred, *cred_tail, *cred_head;
	struct wpa_config *config;
	int id = 0;
	int cred_id = 0;

	if (name == NULL)
		return NULL;
	if (cfgp)
		config = cfgp;
	else
		config = wpa_config_alloc_empty(NULL, NULL);
	if (config == NULL) {
		wpa_printf(MSG_ERROR, "Failed to allocate config file "
			   "structure");
		return NULL;
	}
	tail = head = config->ssid;
	while (tail && tail->next)
		tail = tail->next;
	cred_tail = cred_head = config->cred;
	while (cred_tail && cred_tail->next)
		cred_tail = cred_tail->next;

	wpa_printf(MSG_DEBUG, "Reading configuration file '%s'", name);
	f = fopen(name, "r");
	if (f == NULL) {
		wpa_printf(MSG_ERROR, "Failed to open config file '%s', "
			   "error: %s", name, strerror(errno));
		if (config != cfgp)
			os_free(config);
		return NULL;
	}

	while (wpa_config_get_line(buf, sizeof(buf), f, &line, &pos)) {
		if (os_strcmp(pos, "network={") == 0) {
			ssid = wpa_config_read_network(f, &line, id++);
			if (ssid == NULL) {
				wpa_printf(MSG_ERROR, "Line %d: failed to "
					   "parse network block.", line);
				errors++;
				continue;
			}
			if (head == NULL) {
				head = tail = ssid;
			} else {
				tail->next = ssid;
				tail = ssid;
			}
			if (wpa_config_add_prio_network(config, ssid)) {
				wpa_printf(MSG_ERROR, "Line %d: failed to add "
					   "network block to priority list.",
					   line);
				errors++;
				continue;
			}
		} else if (os_strcmp(pos, "cred={") == 0) {
			cred = wpa_config_read_cred(f, &line, cred_id++);
			if (cred == NULL) {
				wpa_printf(MSG_ERROR, "Line %d: failed to "
					   "parse cred block.", line);
				errors++;
				continue;
			}
			if (cred_head == NULL) {
				cred_head = cred_tail = cred;
			} else {
				cred_tail->next = cred;
				cred_tail = cred;
			}
#ifndef CONFIG_NO_CONFIG_BLOBS
		} else if (os_strncmp(pos, "blob-base64-", 12) == 0) {
			if (wpa_config_process_blob(config, f, &line, pos + 12)
			    < 0) {
				wpa_printf(MSG_ERROR, "Line %d: failed to "
					   "process blob.", line);
				errors++;
				continue;
			}
#endif /* CONFIG_NO_CONFIG_BLOBS */
		} else if (wpa_config_process_global(config, pos, line) < 0) {
			wpa_printf(MSG_ERROR, "Line %d: Invalid configuration "
				   "line '%s'.", line, pos);
			errors++;
			continue;
		}
	}

	fclose(f);

	config->ssid = head;
	wpa_config_debug_dump_networks(config);
	config->cred = cred_head;

#ifndef WPA_IGNORE_CONFIG_ERRORS
	if (errors) {
		if (config != cfgp)
			wpa_config_free(config);
		config = NULL;
		head = NULL;
	}
#endif /* WPA_IGNORE_CONFIG_ERRORS */

	return config;
}