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
struct wpa_global {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_DEBUG ; 
 int /*<<< orphan*/  atoi (char*) ; 
 scalar_t__ os_strcasecmp (char*,char*) ; 
 char* os_strchr (char*,char) ; 
 int /*<<< orphan*/  wifi_display_enable (struct wpa_global*,int) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,char*,char*) ; 

__attribute__((used)) static int wpas_global_ctrl_iface_set(struct wpa_global *global, char *cmd)
{
	char *value;

	value = os_strchr(cmd, ' ');
	if (value == NULL)
		return -1;
	*value++ = '\0';

	wpa_printf(MSG_DEBUG, "GLOBAL_CTRL_IFACE SET '%s'='%s'", cmd, value);

#ifdef CONFIG_WIFI_DISPLAY
	if (os_strcasecmp(cmd, "wifi_display") == 0) {
		wifi_display_enable(global, !!atoi(value));
		return 0;
	}
#endif /* CONFIG_WIFI_DISPLAY */

	/* Restore cmd to its original value to allow redirection */
	value[-1] = ' ';

	return -1;
}