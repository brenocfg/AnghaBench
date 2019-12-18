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
struct wpa_authenticator {int /*<<< orphan*/  cb_ctx; TYPE_1__* cb; } ;
struct TYPE_2__ {int (* update_vlan ) (int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int) ;} ;

/* Variables and functions */
 int stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int) ; 

__attribute__((used)) static int wpa_auth_update_vlan(struct wpa_authenticator *wpa_auth,
				const u8 *addr, int vlan_id)
{
	if (!wpa_auth->cb->update_vlan)
		return -1;
	return wpa_auth->cb->update_vlan(wpa_auth->cb_ctx, addr, vlan_id);
}