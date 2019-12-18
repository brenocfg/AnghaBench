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
struct sta_info {int dummy; } ;
struct hostapd_data {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ieee802_1x_tx_key (struct hostapd_data*,struct sta_info*) ; 

__attribute__((used)) static void _ieee802_1x_tx_key(void *ctx, void *sta_ctx)
{
#ifndef CONFIG_FIPS
#ifndef CONFIG_NO_RC4
	struct hostapd_data *hapd = ctx;
	struct sta_info *sta = sta_ctx;
	ieee802_1x_tx_key(hapd, sta);
#endif /* CONFIG_NO_RC4 */
#endif /* CONFIG_FIPS */
}