#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct hostapd_data {TYPE_1__* wps; } ;
struct TYPE_2__ {int /*<<< orphan*/  registrar; } ;

/* Variables and functions */
 int wps_registrar_get_info (int /*<<< orphan*/ ,int /*<<< orphan*/  const*,char*,size_t) ; 

int hostapd_wps_get_mib_sta(struct hostapd_data *hapd, const u8 *addr,
			    char *buf, size_t buflen)
{
	if (hapd->wps == NULL)
		return 0;
	return wps_registrar_get_info(hapd->wps->registrar, addr, buf, buflen);
}