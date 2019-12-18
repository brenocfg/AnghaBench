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
typedef  int u8 ;
struct wpa_driver_privsep_data {int dummy; } ;
typedef  int /*<<< orphan*/  reply ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_DEBUG ; 
 int /*<<< orphan*/  PRIVSEP_CMD_GET_SSID ; 
 int SSID_MAX_LEN ; 
 int /*<<< orphan*/  os_memcpy (int*,int*,int) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*) ; 
 int wpa_priv_cmd (struct wpa_driver_privsep_data*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int*,size_t*) ; 

__attribute__((used)) static int wpa_driver_privsep_get_ssid(void *priv, u8 *ssid)
{
	struct wpa_driver_privsep_data *drv = priv;
	int res, ssid_len;
	u8 reply[sizeof(int) + SSID_MAX_LEN];
	size_t len = sizeof(reply);

	res = wpa_priv_cmd(drv, PRIVSEP_CMD_GET_SSID, NULL, 0, reply, &len);
	if (res < 0 || len < sizeof(int))
		return -1;
	os_memcpy(&ssid_len, reply, sizeof(int));
	if (ssid_len < 0 || ssid_len > SSID_MAX_LEN ||
	    sizeof(int) + ssid_len > len) {
		wpa_printf(MSG_DEBUG, "privsep: Invalid get SSID reply");
		return -1;
	}
	os_memcpy(ssid, &reply[sizeof(int)], ssid_len);
	return ssid_len;
}