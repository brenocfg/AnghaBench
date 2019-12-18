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
 int atoi (char*) ; 
 int wpa_supplicant_set_bss_expiration_age (struct wpa_supplicant*,int) ; 

__attribute__((used)) static int wpa_supplicant_ctrl_iface_bss_expire_age(
	struct wpa_supplicant *wpa_s, char *cmd)
{
	int expire_age = atoi(cmd);
	return wpa_supplicant_set_bss_expiration_age(wpa_s, expire_age);
}