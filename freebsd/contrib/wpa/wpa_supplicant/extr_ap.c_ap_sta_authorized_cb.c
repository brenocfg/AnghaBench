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

/* Variables and functions */
 int /*<<< orphan*/  wpas_notify_sta_authorized (void*,int /*<<< orphan*/  const*,int,int /*<<< orphan*/  const*) ; 

__attribute__((used)) static void ap_sta_authorized_cb(void *ctx, const u8 *mac_addr,
				 int authorized, const u8 *p2p_dev_addr)
{
	wpas_notify_sta_authorized(ctx, mac_addr, authorized, p2p_dev_addr);
}