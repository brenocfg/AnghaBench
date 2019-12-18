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
typedef  int /*<<< orphan*/  u16 ;
struct wpabuf {int dummy; } ;

/* Variables and functions */
 int WLAN_ACTION_PUBLIC ; 
 int WLAN_PA_GAS_COMEBACK_RESP ; 
 struct wpabuf* wpabuf_alloc (int) ; 
 int /*<<< orphan*/  wpabuf_put_le16 (struct wpabuf*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wpabuf_put_u8 (struct wpabuf*,int) ; 

__attribute__((used)) static struct wpabuf *
gas_build_resp(u8 action, u8 dialog_token, u16 status_code, u8 frag_id,
	       u8 more, u16 comeback_delay, size_t size)
{
	struct wpabuf *buf;

	buf = wpabuf_alloc(100 + size);
	if (buf == NULL)
		return NULL;

	wpabuf_put_u8(buf, WLAN_ACTION_PUBLIC);
	wpabuf_put_u8(buf, action);
	wpabuf_put_u8(buf, dialog_token);
	wpabuf_put_le16(buf, status_code);
	if (action == WLAN_PA_GAS_COMEBACK_RESP)
		wpabuf_put_u8(buf, frag_id | (more ? 0x80 : 0));
	wpabuf_put_le16(buf, comeback_delay);

	return buf;
}