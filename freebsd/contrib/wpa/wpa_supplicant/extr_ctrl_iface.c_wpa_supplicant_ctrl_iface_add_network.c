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
struct wpa_ssid {int /*<<< orphan*/  id; } ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_DEBUG ; 
 int os_snprintf (char*,size_t,char*,int /*<<< orphan*/ ) ; 
 scalar_t__ os_snprintf_error (size_t,int) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*) ; 
 struct wpa_ssid* wpa_supplicant_add_network (struct wpa_supplicant*) ; 

__attribute__((used)) static int wpa_supplicant_ctrl_iface_add_network(
	struct wpa_supplicant *wpa_s, char *buf, size_t buflen)
{
	struct wpa_ssid *ssid;
	int ret;

	wpa_printf(MSG_DEBUG, "CTRL_IFACE: ADD_NETWORK");

	ssid = wpa_supplicant_add_network(wpa_s);
	if (ssid == NULL)
		return -1;

	ret = os_snprintf(buf, buflen, "%d\n", ssid->id);
	if (os_snprintf_error(buflen, ret))
		return -1;
	return ret;
}