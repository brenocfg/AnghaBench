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
struct ikev2_responder_data {int /*<<< orphan*/  IDr_len; int /*<<< orphan*/ * IDr; } ;
struct ikev2_payload_hdr {int /*<<< orphan*/  payload_length; scalar_t__ flags; int /*<<< orphan*/  next_payload; } ;

/* Variables and functions */
 int /*<<< orphan*/  ID_KEY_ID ; 
 int /*<<< orphan*/  MSG_DEBUG ; 
 int /*<<< orphan*/  MSG_INFO ; 
 int /*<<< orphan*/  WPA_PUT_BE16 (int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*) ; 
 struct ikev2_payload_hdr* wpabuf_put (struct wpabuf*,int) ; 
 int /*<<< orphan*/  wpabuf_put_data (struct wpabuf*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wpabuf_put_u8 (struct wpabuf*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ikev2_build_idr(struct ikev2_responder_data *data,
			   struct wpabuf *msg, u8 next_payload)
{
	struct ikev2_payload_hdr *phdr;
	size_t plen;

	wpa_printf(MSG_DEBUG, "IKEV2: Adding IDr payload");

	if (data->IDr == NULL) {
		wpa_printf(MSG_INFO, "IKEV2: No IDr available");
		return -1;
	}

	/* IDr - RFC 4306, Sect. 3.5 */
	phdr = wpabuf_put(msg, sizeof(*phdr));
	phdr->next_payload = next_payload;
	phdr->flags = 0;
	wpabuf_put_u8(msg, ID_KEY_ID);
	wpabuf_put(msg, 3); /* RESERVED */
	wpabuf_put_data(msg, data->IDr, data->IDr_len);
	plen = (u8 *) wpabuf_put(msg, 0) - (u8 *) phdr;
	WPA_PUT_BE16(phdr->payload_length, plen);
	return 0;
}