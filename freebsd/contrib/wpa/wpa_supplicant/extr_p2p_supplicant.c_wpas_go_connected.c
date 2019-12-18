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
struct wpa_supplicant {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/ * wpas_get_p2p_client_iface (struct wpa_supplicant*,int /*<<< orphan*/  const*) ; 

__attribute__((used)) static int wpas_go_connected(void *ctx, const u8 *dev_addr)
{
	struct wpa_supplicant *wpa_s = ctx;

	return wpas_get_p2p_client_iface(wpa_s, dev_addr) != NULL;
}