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
struct wps_button_pushed_ctx {int /*<<< orphan*/  count; int /*<<< orphan*/  const* p2p_dev_addr; } ;
struct hostapd_data {int dummy; } ;
typedef  int /*<<< orphan*/  ctx ;

/* Variables and functions */
 int hostapd_wps_for_each (struct hostapd_data*,int /*<<< orphan*/ ,struct wps_button_pushed_ctx*) ; 
 int /*<<< orphan*/  os_memset (struct wps_button_pushed_ctx*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  wps_button_pushed ; 

int hostapd_wps_button_pushed(struct hostapd_data *hapd,
			      const u8 *p2p_dev_addr)
{
	struct wps_button_pushed_ctx ctx;
	int ret;

	os_memset(&ctx, 0, sizeof(ctx));
	ctx.p2p_dev_addr = p2p_dev_addr;
	ret = hostapd_wps_for_each(hapd, wps_button_pushed, &ctx);
	if (ret == 0 && !ctx.count)
		ret = -1;
	return ret;
}