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
struct wpa_supplicant {int /*<<< orphan*/  conf; } ;
struct wpa_cred {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_DEBUG ; 
 int atoi (char*) ; 
 int /*<<< orphan*/  os_free (char*) ; 
 char* os_strchr (char*,char) ; 
 size_t os_strlcpy (char*,char*,size_t) ; 
 struct wpa_cred* wpa_config_get_cred (int /*<<< orphan*/ ,int) ; 
 char* wpa_config_get_cred_no_key (struct wpa_cred*,char*) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,...) ; 

__attribute__((used)) static int wpa_supplicant_ctrl_iface_get_cred(struct wpa_supplicant *wpa_s,
					      char *cmd, char *buf,
					      size_t buflen)
{
	int id;
	size_t res;
	struct wpa_cred *cred;
	char *name, *value;

	/* cmd: "<cred id> <variable name>" */
	name = os_strchr(cmd, ' ');
	if (name == NULL)
		return -1;
	*name++ = '\0';

	id = atoi(cmd);
	wpa_printf(MSG_DEBUG, "CTRL_IFACE: GET_CRED id=%d name='%s'",
		   id, name);

	cred = wpa_config_get_cred(wpa_s->conf, id);
	if (cred == NULL) {
		wpa_printf(MSG_DEBUG, "CTRL_IFACE: Could not find cred id=%d",
			   id);
		return -1;
	}

	value = wpa_config_get_cred_no_key(cred, name);
	if (value == NULL) {
		wpa_printf(MSG_DEBUG, "CTRL_IFACE: Failed to get cred variable '%s'",
			   name);
		return -1;
	}

	res = os_strlcpy(buf, value, buflen);
	if (res >= buflen) {
		os_free(value);
		return -1;
	}

	os_free(value);

	return res;
}