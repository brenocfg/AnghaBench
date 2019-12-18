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
struct wpabuf {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_DEBUG ; 
 int /*<<< orphan*/  P2P_ATTR_CONFIGURATION_TIMEOUT ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wpabuf_put_le16 (struct wpabuf*,int) ; 
 int /*<<< orphan*/  wpabuf_put_u8 (struct wpabuf*,int /*<<< orphan*/ ) ; 

void p2p_buf_add_config_timeout(struct wpabuf *buf, u8 go_timeout,
				u8 client_timeout)
{
	/* Configuration Timeout */
	wpabuf_put_u8(buf, P2P_ATTR_CONFIGURATION_TIMEOUT);
	wpabuf_put_le16(buf, 2);
	wpabuf_put_u8(buf, go_timeout);
	wpabuf_put_u8(buf, client_timeout);
	wpa_printf(MSG_DEBUG, "P2P: * Configuration Timeout: GO %d (*10ms)  "
		   "client %d (*10ms)", go_timeout, client_timeout);
}