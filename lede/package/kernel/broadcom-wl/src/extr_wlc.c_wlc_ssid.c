#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {size_t SSID_len; int /*<<< orphan*/  SSID; } ;
typedef  TYPE_1__ wlc_ssid_t ;
typedef  int wlc_param ;
typedef  int /*<<< orphan*/  ssid ;

/* Variables and functions */
 int GET ; 
 int PARAM_MODE ; 
 int SET ; 
 int /*<<< orphan*/  WLC_GET_SSID ; 
 int /*<<< orphan*/  WLC_SET_SSID ; 
 int /*<<< orphan*/  interface ; 
 int /*<<< orphan*/  memcpy (char*,int /*<<< orphan*/ ,size_t) ; 
 size_t strlen (void*) ; 
 int /*<<< orphan*/  strncpy (int /*<<< orphan*/ ,void*,int) ; 
 scalar_t__ vif ; 
 int wl_bssiovar_get (int /*<<< orphan*/ ,char*,scalar_t__,TYPE_1__*,int) ; 
 int wl_bssiovar_set (int /*<<< orphan*/ ,char*,scalar_t__,TYPE_1__*,int) ; 
 int wl_ioctl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*,int) ; 

__attribute__((used)) static int wlc_ssid(wlc_param param, void *data, void *value)
{
	int ret = -1, ret2 = -1;
	char *dest = (char *) value;
	wlc_ssid_t ssid;
	
	if ((param & PARAM_MODE) == GET) {
		ret = wl_bssiovar_get(interface, "ssid", vif, &ssid, sizeof(ssid));

		if (ret)
			/* if we can't get the ssid through the bssiovar, try WLC_GET_SSID */
			ret = wl_ioctl(interface, WLC_GET_SSID, &ssid, sizeof(ssid));
		
		if (!ret) {
			memcpy(dest, ssid.SSID, ssid.SSID_len);
			dest[ssid.SSID_len] = 0;
		}
	} else if ((param & PARAM_MODE) == SET) {
		strncpy(ssid.SSID, value, 32);
		ssid.SSID_len = strlen(value);
		
		if (ssid.SSID_len > 32)
			ssid.SSID_len = 32;
		
		if (vif == 0) {
			/* for the main interface, also try the WLC_SET_SSID call */
			ret2 = wl_ioctl(interface, WLC_SET_SSID, &ssid, sizeof(ssid));
		}
		
		ret = wl_bssiovar_set(interface, "ssid", vif, &ssid, sizeof(ssid));
		ret = (!ret2 ? 0 : ret);
	}
	
	return ret;
}