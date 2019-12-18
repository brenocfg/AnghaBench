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
struct TYPE_2__ {int (* sta_set_flags ) (int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int,int,int) ;} ;

/* Variables and functions */
 int stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int,int,int) ; 

__attribute__((used)) static inline int wpa_drv_sta_set_flags(struct wpa_supplicant *wpa_s,
					const u8 *addr, int total_flags,
					int flags_or, int flags_and)
{
	if (wpa_s->driver->sta_set_flags)
		return wpa_s->driver->sta_set_flags(wpa_s->drv_priv, addr,
						    total_flags, flags_or,
						    flags_and);
	return -1;
}