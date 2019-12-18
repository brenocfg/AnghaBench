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
typedef  int /*<<< orphan*/  u32 ;
typedef  int /*<<< orphan*/  u16 ;
struct wpa_sm {int dummy; } ;

/* Variables and functions */
 int wpa_sm_send_tdls_mgmt (struct wpa_sm*,int /*<<< orphan*/  const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/  const*,size_t) ; 

__attribute__((used)) static int wpa_tdls_send_tpk_msg(struct wpa_sm *sm, const u8 *dst,
				 u8 action_code, u8 dialog_token,
				 u16 status_code, u32 peer_capab,
				 int initiator, const u8 *buf, size_t len)
{
	return wpa_sm_send_tdls_mgmt(sm, dst, action_code, dialog_token,
				     status_code, peer_capab, initiator, buf,
				     len);
}