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
typedef  int /*<<< orphan*/  u16 ;
struct ibss_rsn {int /*<<< orphan*/  wpa_s; } ;

/* Variables and functions */
 int /*<<< orphan*/  wpa_drv_sta_deauth (int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ibss_rsn_disconnect(void *ctx, const u8 *addr, u16 reason)
{
	struct ibss_rsn *ibss_rsn = ctx;
	wpa_drv_sta_deauth(ibss_rsn->wpa_s, addr, reason);
}