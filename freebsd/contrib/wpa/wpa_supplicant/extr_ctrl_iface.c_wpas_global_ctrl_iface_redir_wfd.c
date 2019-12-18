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
struct wpa_global {int /*<<< orphan*/ * p2p_init_wpa_s; } ;

/* Variables and functions */
 scalar_t__ os_strncmp (char*,char*,int) ; 
 char* wpa_supplicant_ctrl_iface_process (int /*<<< orphan*/ *,char*,size_t*) ; 

__attribute__((used)) static char * wpas_global_ctrl_iface_redir_wfd(struct wpa_global *global,
					       char *buf, size_t *resp_len)
{
#ifdef CONFIG_WIFI_DISPLAY
	if (global->p2p_init_wpa_s == NULL)
		return NULL;
	if (os_strncmp(buf, "WFD_SUBELEM_SET ", 16) == 0 ||
	    os_strncmp(buf, "WFD_SUBELEM_GET ", 16) == 0)
		return wpa_supplicant_ctrl_iface_process(global->p2p_init_wpa_s,
							 buf, resp_len);
#endif /* CONFIG_WIFI_DISPLAY */
	return NULL;
}