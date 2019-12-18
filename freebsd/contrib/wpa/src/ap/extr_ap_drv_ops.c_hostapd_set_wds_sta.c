#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct hostapd_data {int /*<<< orphan*/  drv_priv; TYPE_2__* driver; TYPE_1__* conf; } ;
struct TYPE_4__ {int (* set_wds_sta ) (int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int,int,char const*,char*) ;} ;
struct TYPE_3__ {char* wds_bridge; char* bridge; } ;

/* Variables and functions */
 int stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int,int,char const*,char*) ; 

int hostapd_set_wds_sta(struct hostapd_data *hapd, char *ifname_wds,
			const u8 *addr, int aid, int val)
{
	const char *bridge = NULL;

	if (hapd->driver == NULL || hapd->driver->set_wds_sta == NULL)
		return -1;
	if (hapd->conf->wds_bridge[0])
		bridge = hapd->conf->wds_bridge;
	else if (hapd->conf->bridge[0])
		bridge = hapd->conf->bridge;
	return hapd->driver->set_wds_sta(hapd->drv_priv, addr, aid, val,
					 bridge, ifname_wds);
}