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
struct wpa_supplicant {struct bgscan_ops const* bgscan; int /*<<< orphan*/ * bgscan_priv; } ;
struct wpa_ssid {int dummy; } ;
struct bgscan_ops {int /*<<< orphan*/  name; int /*<<< orphan*/ * (* init ) (struct wpa_supplicant*,char const*,struct wpa_ssid*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_DEBUG ; 
 int /*<<< orphan*/  MSG_ERROR ; 
 int /*<<< orphan*/  bgscan_deinit (struct wpa_supplicant*) ; 
 struct bgscan_ops** bgscan_modules ; 
 char* os_strchr (char const*,char) ; 
 size_t os_strlen (char const*) ; 
 scalar_t__ os_strncmp (char const*,int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/ * stub1 (struct wpa_supplicant*,char const*,struct wpa_ssid*) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,char const*,...) ; 

int bgscan_init(struct wpa_supplicant *wpa_s, struct wpa_ssid *ssid,
		const char *name)
{
	const char *params;
	size_t nlen;
	int i;
	const struct bgscan_ops *ops = NULL;

	bgscan_deinit(wpa_s);

	params = os_strchr(name, ':');
	if (params == NULL) {
		params = "";
		nlen = os_strlen(name);
	} else {
		nlen = params - name;
		params++;
	}

	for (i = 0; bgscan_modules[i]; i++) {
		if (os_strncmp(name, bgscan_modules[i]->name, nlen) == 0) {
			ops = bgscan_modules[i];
			break;
		}
	}

	if (ops == NULL) {
		wpa_printf(MSG_ERROR, "bgscan: Could not find module "
			   "matching the parameter '%s'", name);
		return -1;
	}

	wpa_s->bgscan_priv = ops->init(wpa_s, params, ssid);
	if (wpa_s->bgscan_priv == NULL)
		return -1;
	wpa_s->bgscan = ops;
	wpa_printf(MSG_DEBUG, "bgscan: Initialized module '%s' with "
		   "parameters '%s'", ops->name, params);

	return 0;
}