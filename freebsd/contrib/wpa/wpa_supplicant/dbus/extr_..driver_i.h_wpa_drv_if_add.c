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
struct wpa_supplicant {int /*<<< orphan*/  drv_priv; TYPE_1__* driver; } ;
typedef  enum wpa_driver_if_type { ____Placeholder_wpa_driver_if_type } wpa_driver_if_type ;
struct TYPE_2__ {int (* if_add ) (int /*<<< orphan*/ ,int,char const*,int /*<<< orphan*/  const*,void*,int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int stub1 (int /*<<< orphan*/ ,int,char const*,int /*<<< orphan*/  const*,void*,int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline int wpa_drv_if_add(struct wpa_supplicant *wpa_s,
				 enum wpa_driver_if_type type,
				 const char *ifname, const u8 *addr,
				 void *bss_ctx, char *force_ifname,
				 u8 *if_addr, const char *bridge)
{
	if (wpa_s->driver->if_add)
		return wpa_s->driver->if_add(wpa_s->drv_priv, type, ifname,
					     addr, bss_ctx, NULL, force_ifname,
					     if_addr, bridge, 0, 0);
	return -1;
}