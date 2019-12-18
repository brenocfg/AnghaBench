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
struct hostapd_data {int dummy; } ;

/* Variables and functions */
 int michael_mic_failure (struct hostapd_data*,int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int hostapd_wpa_auth_mic_failure_report(void *ctx, const u8 *addr)
{
	struct hostapd_data *hapd = ctx;
	return michael_mic_failure(hapd, addr, 0);
}