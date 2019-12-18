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
struct p2p_message {void* p2p_attributes; void* wps_attributes; } ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_DEBUG ; 
 int /*<<< orphan*/  MSG_MSGDUMP ; 
 int /*<<< orphan*/  os_memset (struct p2p_message*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  p2p_parse_free (struct p2p_message*) ; 
 scalar_t__ p2p_parse_p2p_ie (void*,struct p2p_message*) ; 
 scalar_t__ p2p_parse_wps_ie (void*,struct p2p_message*) ; 
 int /*<<< orphan*/  wpa_hexdump_buf (int /*<<< orphan*/ ,char*,void*) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*) ; 
 void* wpabuf_alloc_copy (int /*<<< orphan*/  const*,size_t) ; 

int p2p_parse_ies_separate(const u8 *wsc, size_t wsc_len, const u8 *p2p,
			   size_t p2p_len, struct p2p_message *msg)
{
	os_memset(msg, 0, sizeof(*msg));

	msg->wps_attributes = wpabuf_alloc_copy(wsc, wsc_len);
	if (msg->wps_attributes &&
	    p2p_parse_wps_ie(msg->wps_attributes, msg)) {
		p2p_parse_free(msg);
		return -1;
	}

	msg->p2p_attributes = wpabuf_alloc_copy(p2p, p2p_len);
	if (msg->p2p_attributes &&
	    p2p_parse_p2p_ie(msg->p2p_attributes, msg)) {
		wpa_printf(MSG_DEBUG, "P2P: Failed to parse P2P IE data");
		if (msg->p2p_attributes)
			wpa_hexdump_buf(MSG_MSGDUMP, "P2P: P2P IE data",
					msg->p2p_attributes);
		p2p_parse_free(msg);
		return -1;
	}

	return 0;
}