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
typedef  int /*<<< orphan*/  u32 ;
struct eap_tnc_data {int /*<<< orphan*/ * in_buf; } ;

/* Variables and functions */
 int EAP_TNC_FLAGS_LENGTH_INCLUDED ; 
 int /*<<< orphan*/  MSG_DEBUG ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/ * wpabuf_alloc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wpabuf_put_data (int /*<<< orphan*/ *,int const*,size_t) ; 
 scalar_t__ wpabuf_tailroom (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int eap_tnc_process_fragment(struct eap_tnc_data *data,
				    u8 flags, u32 message_length,
				    const u8 *buf, size_t len)
{
	/* Process a fragment that is not the last one of the message */
	if (data->in_buf == NULL && !(flags & EAP_TNC_FLAGS_LENGTH_INCLUDED)) {
		wpa_printf(MSG_DEBUG, "EAP-TNC: No Message Length field in a "
			   "fragmented packet");
		return -1;
	}

	if (data->in_buf == NULL) {
		/* First fragment of the message */
		data->in_buf = wpabuf_alloc(message_length);
		if (data->in_buf == NULL) {
			wpa_printf(MSG_DEBUG, "EAP-TNC: No memory for "
				   "message");
			return -1;
		}
		wpabuf_put_data(data->in_buf, buf, len);
		wpa_printf(MSG_DEBUG, "EAP-TNC: Received %lu bytes in first "
			   "fragment, waiting for %lu bytes more",
			   (unsigned long) len,
			   (unsigned long) wpabuf_tailroom(data->in_buf));
	}

	return 0;
}