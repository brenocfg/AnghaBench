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
struct eap_wsc_data {int in_op_code; int /*<<< orphan*/ * in_buf; } ;
struct eap_method_ret {void* ignore; } ;

/* Variables and functions */
 int /*<<< orphan*/  EAP_CODE_RESPONSE ; 
 int /*<<< orphan*/  MSG_DEBUG ; 
 void* TRUE ; 
 int WSC_FLAGS_LF ; 
 struct wpabuf* eap_wsc_build_frag_ack (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/ * wpabuf_alloc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wpabuf_put_data (int /*<<< orphan*/ *,int const*,size_t) ; 
 scalar_t__ wpabuf_tailroom (int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct wpabuf * eap_wsc_process_fragment(struct eap_wsc_data *data,
						struct eap_method_ret *ret,
						u8 id, u8 flags, u8 op_code,
						u16 message_length,
						const u8 *buf, size_t len)
{
	/* Process a fragment that is not the last one of the message */
	if (data->in_buf == NULL && !(flags & WSC_FLAGS_LF)) {
		wpa_printf(MSG_DEBUG, "EAP-WSC: No Message Length field in a "
			   "fragmented packet");
		ret->ignore = TRUE;
		return NULL;
	}

	if (data->in_buf == NULL) {
		/* First fragment of the message */
		data->in_buf = wpabuf_alloc(message_length);
		if (data->in_buf == NULL) {
			wpa_printf(MSG_DEBUG, "EAP-WSC: No memory for "
				   "message");
			ret->ignore = TRUE;
			return NULL;
		}
		data->in_op_code = op_code;
		wpabuf_put_data(data->in_buf, buf, len);
		wpa_printf(MSG_DEBUG, "EAP-WSC: Received %lu bytes in first "
			   "fragment, waiting for %lu bytes more",
			   (unsigned long) len,
			   (unsigned long) wpabuf_tailroom(data->in_buf));
	}

	return eap_wsc_build_frag_ack(id, EAP_CODE_RESPONSE);
}