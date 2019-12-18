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
struct wpabuf {int dummy; } ;

/* Variables and functions */
#define  WLAN_PA_GAS_COMEBACK_RESP 130 
#define  WLAN_PA_GAS_INITIAL_REQ 129 
#define  WLAN_PA_GAS_INITIAL_RESP 128 
 int /*<<< orphan*/  WPA_PUT_LE16 (int*,int) ; 
 int* wpabuf_head_u8 (struct wpabuf*) ; 
 size_t wpabuf_len (struct wpabuf*) ; 
 int* wpabuf_mhead_u8 (struct wpabuf*) ; 
 scalar_t__ wpabuf_put (struct wpabuf*,int /*<<< orphan*/ ) ; 

void gas_anqp_set_len(struct wpabuf *buf)
{
	u8 action;
	size_t offset;
	u8 *len;

	if (buf == NULL || wpabuf_len(buf) < 2)
		return;

	action = *(wpabuf_head_u8(buf) + 1);
	switch (action) {
	case WLAN_PA_GAS_INITIAL_REQ:
		offset = 3 + 4;
		break;
	case WLAN_PA_GAS_INITIAL_RESP:
		offset = 7 + 4;
		break;
	case WLAN_PA_GAS_COMEBACK_RESP:
		offset = 8 + 4;
		break;
	default:
		return;
	}

	if (wpabuf_len(buf) < offset + 2)
		return;

	len = wpabuf_mhead_u8(buf) + offset;
	WPA_PUT_LE16(len, (u8 *) wpabuf_put(buf, 0) - len - 2);
}