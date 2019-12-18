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
struct eap_wsc_data {int in_op_code; int /*<<< orphan*/ * in_buf; } ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_DEBUG ; 
 int WSC_FLAGS_LF ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/ * wpabuf_alloc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wpabuf_put_data (int /*<<< orphan*/ *,int const*,size_t) ; 
 scalar_t__ wpabuf_tailroom (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int eap_wsc_process_fragment(struct eap_wsc_data *data,
				    u8 flags, u8 op_code, u16 message_length,
				    const u8 *buf, size_t len)
{
	/* Process a fragment that is not the last one of the message */
	if (data->in_buf == NULL && !(flags & WSC_FLAGS_LF)) {
		wpa_printf(MSG_DEBUG, "EAP-WSC: No Message Length "
			   "field in a fragmented packet");
		return -1;
	}

	if (data->in_buf == NULL) {
		/* First fragment of the message */
		data->in_buf = wpabuf_alloc(message_length);
		if (data->in_buf == NULL) {
			wpa_printf(MSG_DEBUG, "EAP-WSC: No memory for "
				   "message");
			return -1;
		}
		data->in_op_code = op_code;
		wpabuf_put_data(data->in_buf, buf, len);
		wpa_printf(MSG_DEBUG, "EAP-WSC: Received %lu bytes in "
			   "first fragment, waiting for %lu bytes more",
			   (unsigned long) len,
			   (unsigned long) wpabuf_tailroom(data->in_buf));
	}

	return 0;
}