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
typedef  int u8 ;
struct wpa_supplicant {int dummy; } ;
typedef  int /*<<< orphan*/  reject_attr ;
typedef  enum mbo_transition_reject_reason { ____Placeholder_mbo_transition_reject_reason } mbo_transition_reject_reason ;

/* Variables and functions */
 int MBO_ATTR_ID_TRANSITION_REJECT_REASON ; 
 size_t mbo_add_ie (int*,size_t,int*,int) ; 

size_t wpas_mbo_ie_bss_trans_reject(struct wpa_supplicant *wpa_s, u8 *pos,
				    size_t len,
				    enum mbo_transition_reject_reason reason)
{
	u8 reject_attr[3];

	reject_attr[0] = MBO_ATTR_ID_TRANSITION_REJECT_REASON;
	reject_attr[1] = 1;
	reject_attr[2] = reason;

	return mbo_add_ie(pos, len, reject_attr, sizeof(reject_attr));
}