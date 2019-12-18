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
struct TYPE_2__ {int /*<<< orphan*/  const* (* get_psk ) (int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,size_t*,int*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  const* stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,size_t*,int*) ; 

__attribute__((used)) static inline const u8 * wpa_auth_get_psk(struct wpa_authenticator *wpa_auth,
					  const u8 *addr,
					  const u8 *p2p_dev_addr,
					  const u8 *prev_psk, size_t *psk_len,
					  int *vlan_id)
{
	if (wpa_auth->cb->get_psk == NULL)
		return NULL;
	return wpa_auth->cb->get_psk(wpa_auth->cb_ctx, addr, p2p_dev_addr,
				     prev_psk, psk_len, vlan_id);
}