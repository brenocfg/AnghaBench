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
struct hostapd_data {int /*<<< orphan*/  drv_priv; TYPE_1__* driver; } ;
struct hostap_sta_driver_data {int dummy; } ;
struct TYPE_2__ {int (* read_sta_data ) (int /*<<< orphan*/ ,struct hostap_sta_driver_data*,int /*<<< orphan*/  const*) ;} ;

/* Variables and functions */
 int stub1 (int /*<<< orphan*/ ,struct hostap_sta_driver_data*,int /*<<< orphan*/  const*) ; 

__attribute__((used)) static inline int hostapd_drv_read_sta_data(
	struct hostapd_data *hapd, struct hostap_sta_driver_data *data,
	const u8 *addr)
{
	if (hapd->driver == NULL || hapd->driver->read_sta_data == NULL)
		return -1;
	return hapd->driver->read_sta_data(hapd->drv_priv, data, addr);
}