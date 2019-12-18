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
struct wpa_supplicant {scalar_t__ ext_work_id; } ;
struct wpa_external_work {char* type; scalar_t__ id; void* timeout; } ;

/* Variables and functions */
 void* atoi (char*) ; 
 int /*<<< orphan*/  os_free (struct wpa_external_work*) ; 
 int /*<<< orphan*/  os_memcpy (char*,char*,size_t) ; 
 int os_snprintf (char*,size_t,char*,scalar_t__) ; 
 scalar_t__ os_snprintf_error (size_t,int) ; 
 char* os_strchr (char*,char) ; 
 int /*<<< orphan*/  os_strlcpy (char*,char*,int) ; 
 size_t os_strlen (char*) ; 
 char* os_strstr (char*,char*) ; 
 struct wpa_external_work* os_zalloc (int) ; 
 scalar_t__ radio_add_work (struct wpa_supplicant*,unsigned int,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct wpa_external_work*) ; 
 int /*<<< orphan*/  wpas_ctrl_radio_work_cb ; 

__attribute__((used)) static int wpas_ctrl_radio_work_add(struct wpa_supplicant *wpa_s, char *cmd,
				    char *buf, size_t buflen)
{
	struct wpa_external_work *ework;
	char *pos, *pos2;
	size_t type_len;
	int ret;
	unsigned int freq = 0;

	/* format: <name> [freq=<MHz>] [timeout=<seconds>] */

	ework = os_zalloc(sizeof(*ework));
	if (ework == NULL)
		return -1;

	pos = os_strchr(cmd, ' ');
	if (pos) {
		type_len = pos - cmd;
		pos++;

		pos2 = os_strstr(pos, "freq=");
		if (pos2)
			freq = atoi(pos2 + 5);

		pos2 = os_strstr(pos, "timeout=");
		if (pos2)
			ework->timeout = atoi(pos2 + 8);
	} else {
		type_len = os_strlen(cmd);
	}
	if (4 + type_len >= sizeof(ework->type))
		type_len = sizeof(ework->type) - 4 - 1;
	os_strlcpy(ework->type, "ext:", sizeof(ework->type));
	os_memcpy(ework->type + 4, cmd, type_len);
	ework->type[4 + type_len] = '\0';

	wpa_s->ext_work_id++;
	if (wpa_s->ext_work_id == 0)
		wpa_s->ext_work_id++;
	ework->id = wpa_s->ext_work_id;

	if (radio_add_work(wpa_s, freq, ework->type, 0, wpas_ctrl_radio_work_cb,
			   ework) < 0) {
		os_free(ework);
		return -1;
	}

	ret = os_snprintf(buf, buflen, "%u", ework->id);
	if (os_snprintf_error(buflen, ret))
		return -1;
	return ret;
}