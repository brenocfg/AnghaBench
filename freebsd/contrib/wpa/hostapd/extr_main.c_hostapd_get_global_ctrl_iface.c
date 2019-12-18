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
struct hapd_interfaces {char* global_iface_name; int /*<<< orphan*/ * global_iface_path; } ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_ERROR ; 
 int /*<<< orphan*/  os_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * os_strdup (char const*) ; 
 char* os_strrchr (int /*<<< orphan*/ *,char) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int hostapd_get_global_ctrl_iface(struct hapd_interfaces *interfaces,
					 const char *path)
{
#ifndef CONFIG_CTRL_IFACE_UDP
	char *pos;
#endif /* !CONFIG_CTRL_IFACE_UDP */

	os_free(interfaces->global_iface_path);
	interfaces->global_iface_path = os_strdup(path);
	if (interfaces->global_iface_path == NULL)
		return -1;

#ifndef CONFIG_CTRL_IFACE_UDP
	pos = os_strrchr(interfaces->global_iface_path, '/');
	if (pos == NULL) {
		wpa_printf(MSG_ERROR, "No '/' in the global control interface "
			   "file");
		os_free(interfaces->global_iface_path);
		interfaces->global_iface_path = NULL;
		return -1;
	}

	*pos = '\0';
	interfaces->global_iface_name = pos + 1;
#endif /* !CONFIG_CTRL_IFACE_UDP */

	return 0;
}