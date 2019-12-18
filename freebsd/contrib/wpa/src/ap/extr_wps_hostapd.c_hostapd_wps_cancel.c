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
struct wps_cancel_ctx {int /*<<< orphan*/  count; } ;
struct hostapd_data {int dummy; } ;
typedef  int /*<<< orphan*/  ctx ;

/* Variables and functions */
 int hostapd_wps_for_each (struct hostapd_data*,int /*<<< orphan*/ ,struct wps_cancel_ctx*) ; 
 int /*<<< orphan*/  os_memset (struct wps_cancel_ctx*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  wps_cancel ; 

int hostapd_wps_cancel(struct hostapd_data *hapd)
{
	struct wps_cancel_ctx ctx;
	int ret;

	os_memset(&ctx, 0, sizeof(ctx));
	ret = hostapd_wps_for_each(hapd, wps_cancel, &ctx);
	if (ret == 0 && !ctx.count)
		ret = -1;
	return ret;
}