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
 int /*<<< orphan*/  WPA_PUT_LE16 (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ * wpabuf_put (struct wpabuf*,int) ; 
 int /*<<< orphan*/  wpabuf_put_u8 (struct wpabuf*,int /*<<< orphan*/ ) ; 
 int wpabuf_tailroom (struct wpabuf*) ; 

__attribute__((used)) static void wpas_sd_add_empty(struct wpabuf *resp, u8 srv_proto,
			      u8 srv_trans_id, u8 status)
{
	u8 *len_pos;

	if (wpabuf_tailroom(resp) < 5)
		return;

	/* Length (to be filled) */
	len_pos = wpabuf_put(resp, 2);
	wpabuf_put_u8(resp, srv_proto);
	wpabuf_put_u8(resp, srv_trans_id);
	/* Status Code */
	wpabuf_put_u8(resp, status);
	/* Response Data: empty */
	WPA_PUT_LE16(len_pos, (u8 *) wpabuf_put(resp, 0) - len_pos - 2);
}