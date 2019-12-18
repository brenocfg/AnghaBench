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
typedef  scalar_t__ u16 ;
struct wpabuf {int dummy; } ;
struct hostapd_data {int dummy; } ;
struct anqp_element {int /*<<< orphan*/  payload; } ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_DEBUG ; 
 struct anqp_element* get_anqp_elem (struct hostapd_data*,scalar_t__) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,scalar_t__) ; 
 scalar_t__ wpabuf_len (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wpabuf_put_buf (struct wpabuf*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wpabuf_put_le16 (struct wpabuf*,scalar_t__) ; 
 scalar_t__ wpabuf_tailroom (struct wpabuf*) ; 

__attribute__((used)) static void anqp_add_elem(struct hostapd_data *hapd, struct wpabuf *buf,
			  u16 infoid)
{
	struct anqp_element *elem;

	elem = get_anqp_elem(hapd, infoid);
	if (!elem)
		return;
	if (wpabuf_tailroom(buf) < 2 + 2 + wpabuf_len(elem->payload)) {
		wpa_printf(MSG_DEBUG, "ANQP: No room for InfoID %u payload",
			   infoid);
		return;
	}

	wpabuf_put_le16(buf, infoid);
	wpabuf_put_le16(buf, wpabuf_len(elem->payload));
	wpabuf_put_buf(buf, elem->payload);
}