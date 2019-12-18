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
struct hostapd_data {int /*<<< orphan*/  wpa_auth; } ;

/* Variables and functions */
 int wpa_auth_pmksa_list (int /*<<< orphan*/ ,char*,size_t) ; 

int hostapd_ctrl_iface_pmksa_list(struct hostapd_data *hapd, char *buf,
				  size_t len)
{
	return wpa_auth_pmksa_list(hapd->wpa_auth, buf, len);
}