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
struct wpa_supplicant {int dummy; } ;

/* Variables and functions */
 scalar_t__ os_strcmp (char*,char*) ; 
 scalar_t__ os_strncmp (char*,char*,int) ; 
 int wpas_ctrl_radio_work_add (struct wpa_supplicant*,char*,char*,size_t) ; 
 int wpas_ctrl_radio_work_done (struct wpa_supplicant*,char*) ; 
 int wpas_ctrl_radio_work_show (struct wpa_supplicant*,char*,size_t) ; 

__attribute__((used)) static int wpas_ctrl_radio_work(struct wpa_supplicant *wpa_s, char *cmd,
				char *buf, size_t buflen)
{
	if (os_strcmp(cmd, "show") == 0)
		return wpas_ctrl_radio_work_show(wpa_s, buf, buflen);
	if (os_strncmp(cmd, "add ", 4) == 0)
		return wpas_ctrl_radio_work_add(wpa_s, cmd + 4, buf, buflen);
	if (os_strncmp(cmd, "done ", 5) == 0)
		return wpas_ctrl_radio_work_done(wpa_s, cmd + 4);
	return -1;
}