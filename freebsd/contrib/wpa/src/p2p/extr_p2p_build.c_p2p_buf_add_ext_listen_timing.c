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
typedef  int u16 ;
struct wpabuf {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_DEBUG ; 
 int /*<<< orphan*/  P2P_ATTR_EXT_LISTEN_TIMING ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,int,int) ; 
 int /*<<< orphan*/  wpabuf_put_le16 (struct wpabuf*,int) ; 
 int /*<<< orphan*/  wpabuf_put_u8 (struct wpabuf*,int /*<<< orphan*/ ) ; 

void p2p_buf_add_ext_listen_timing(struct wpabuf *buf, u16 period,
				   u16 interval)
{
	/* Extended Listen Timing */
	wpabuf_put_u8(buf, P2P_ATTR_EXT_LISTEN_TIMING);
	wpabuf_put_le16(buf, 4);
	wpabuf_put_le16(buf, period);
	wpabuf_put_le16(buf, interval);
	wpa_printf(MSG_DEBUG, "P2P: * Extended Listen Timing (period %u msec  "
		   "interval %u msec)", period, interval);
}