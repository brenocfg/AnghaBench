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
struct wpa_supplicant {int /*<<< orphan*/ * ext_pw; int /*<<< orphan*/  eapol; TYPE_1__* conf; } ;
struct TYPE_2__ {int /*<<< orphan*/  ext_password_backend; } ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_DEBUG ; 
 int /*<<< orphan*/  eapol_sm_set_ext_pw_ctx (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ext_password_deinit (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * ext_password_init (char*,char*) ; 
 int /*<<< orphan*/  os_free (char*) ; 
 char* os_strchr (char*,char) ; 
 char* os_strdup (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,...) ; 

int wpas_init_ext_pw(struct wpa_supplicant *wpa_s)
{
	char *val, *pos;

	ext_password_deinit(wpa_s->ext_pw);
	wpa_s->ext_pw = NULL;
	eapol_sm_set_ext_pw_ctx(wpa_s->eapol, NULL);

	if (!wpa_s->conf->ext_password_backend)
		return 0;

	val = os_strdup(wpa_s->conf->ext_password_backend);
	if (val == NULL)
		return -1;
	pos = os_strchr(val, ':');
	if (pos)
		*pos++ = '\0';

	wpa_printf(MSG_DEBUG, "EXT PW: Initialize backend '%s'", val);

	wpa_s->ext_pw = ext_password_init(val, pos);
	os_free(val);
	if (wpa_s->ext_pw == NULL) {
		wpa_printf(MSG_DEBUG, "EXT PW: Failed to initialize backend");
		return -1;
	}
	eapol_sm_set_ext_pw_ctx(wpa_s->eapol, wpa_s->ext_pw);

	return 0;
}