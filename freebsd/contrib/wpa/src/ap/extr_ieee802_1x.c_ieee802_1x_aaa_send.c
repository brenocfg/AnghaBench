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
struct sta_info {int dummy; } ;
struct hostapd_data {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ieee802_1x_encapsulate_radius (struct hostapd_data*,struct sta_info*,int /*<<< orphan*/  const*,size_t) ; 

__attribute__((used)) static void ieee802_1x_aaa_send(void *ctx, void *sta_ctx,
				const u8 *data, size_t datalen)
{
#ifndef CONFIG_NO_RADIUS
	struct hostapd_data *hapd = ctx;
	struct sta_info *sta = sta_ctx;

	ieee802_1x_encapsulate_radius(hapd, sta, data, datalen);
#endif /* CONFIG_NO_RADIUS */
}