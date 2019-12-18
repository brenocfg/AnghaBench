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
struct TYPE_4__ {int /*<<< orphan*/  key; } ;
struct ubus_banned_client {TYPE_2__ avl; int /*<<< orphan*/  addr; } ;
struct TYPE_3__ {int /*<<< orphan*/  banned; } ;
struct hostapd_data {TYPE_1__ ubus; } ;

/* Variables and functions */
 int /*<<< orphan*/  avl ; 
 struct ubus_banned_client* avl_find_element (int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct ubus_banned_client*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  avl_insert (int /*<<< orphan*/ *,TYPE_2__*) ; 
 int /*<<< orphan*/  eloop_cancel_timeout (int /*<<< orphan*/  (*) (struct ubus_banned_client*,struct hostapd_data*),struct ubus_banned_client*,struct hostapd_data*) ; 
 int /*<<< orphan*/  eloop_register_timeout (int /*<<< orphan*/ ,int,int /*<<< orphan*/  (*) (struct ubus_banned_client*,struct hostapd_data*),struct ubus_banned_client*,struct hostapd_data*) ; 
 int /*<<< orphan*/  hostapd_bss_del_ban (struct ubus_banned_client*,struct hostapd_data*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 struct ubus_banned_client* os_zalloc (int) ; 

__attribute__((used)) static void
hostapd_bss_ban_client(struct hostapd_data *hapd, u8 *addr, int time)
{
	struct ubus_banned_client *ban;

	if (time < 0)
		time = 0;

	ban = avl_find_element(&hapd->ubus.banned, addr, ban, avl);
	if (!ban) {
		if (!time)
			return;

		ban = os_zalloc(sizeof(*ban));
		memcpy(ban->addr, addr, sizeof(ban->addr));
		ban->avl.key = ban->addr;
		avl_insert(&hapd->ubus.banned, &ban->avl);
	} else {
		eloop_cancel_timeout(hostapd_bss_del_ban, ban, hapd);
		if (!time) {
			hostapd_bss_del_ban(ban, hapd);
			return;
		}
	}

	eloop_register_timeout(0, time * 1000, hostapd_bss_del_ban, ban, hapd);
}