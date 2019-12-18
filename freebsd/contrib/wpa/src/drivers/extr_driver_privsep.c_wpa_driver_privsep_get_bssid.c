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
typedef  int /*<<< orphan*/  u8 ;
struct wpa_driver_privsep_data {int dummy; } ;

/* Variables and functions */
 size_t ETH_ALEN ; 
 int /*<<< orphan*/  PRIVSEP_CMD_GET_BSSID ; 
 int wpa_priv_cmd (struct wpa_driver_privsep_data*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,size_t*) ; 

__attribute__((used)) static int wpa_driver_privsep_get_bssid(void *priv, u8 *bssid)
{
	struct wpa_driver_privsep_data *drv = priv;
	int res;
	size_t len = ETH_ALEN;

	res = wpa_priv_cmd(drv, PRIVSEP_CMD_GET_BSSID, NULL, 0, bssid, &len);
	if (res < 0 || len != ETH_ALEN)
		return -1;
	return 0;
}