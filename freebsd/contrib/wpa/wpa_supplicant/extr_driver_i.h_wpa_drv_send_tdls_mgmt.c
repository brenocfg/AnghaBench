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
typedef  int /*<<< orphan*/  u32 ;
typedef  int /*<<< orphan*/  u16 ;
struct wpa_supplicant {int /*<<< orphan*/  drv_priv; TYPE_1__* driver; } ;
struct TYPE_2__ {int (* send_tdls_mgmt ) (int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/  const*,size_t) ;} ;

/* Variables and functions */
 int stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/  const*,size_t) ; 

__attribute__((used)) static inline int wpa_drv_send_tdls_mgmt(struct wpa_supplicant *wpa_s,
					 const u8 *dst, u8 action_code,
					 u8 dialog_token, u16 status_code,
					 u32 peer_capab, int initiator,
					 const u8 *buf, size_t len)
{
	if (wpa_s->driver->send_tdls_mgmt) {
		return wpa_s->driver->send_tdls_mgmt(wpa_s->drv_priv, dst,
						     action_code, dialog_token,
						     status_code, peer_capab,
						     initiator, buf, len);
	}
	return -1;
}