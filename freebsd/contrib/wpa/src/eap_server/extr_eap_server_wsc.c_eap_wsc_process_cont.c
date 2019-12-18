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
typedef  scalar_t__ u8 ;
struct eap_wsc_data {scalar_t__ in_op_code; int /*<<< orphan*/  in_buf; } ;

/* Variables and functions */
 int /*<<< orphan*/  FAIL ; 
 int /*<<< orphan*/  MSG_DEBUG ; 
 int /*<<< orphan*/  eap_wsc_state (struct eap_wsc_data*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  wpabuf_put_data (int /*<<< orphan*/ ,scalar_t__ const*,size_t) ; 
 size_t wpabuf_tailroom (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int eap_wsc_process_cont(struct eap_wsc_data *data,
				const u8 *buf, size_t len, u8 op_code)
{
	/* Process continuation of a pending message */
	if (op_code != data->in_op_code) {
		wpa_printf(MSG_DEBUG, "EAP-WSC: Unexpected Op-Code %d in "
			   "fragment (expected %d)",
			   op_code, data->in_op_code);
		eap_wsc_state(data, FAIL);
		return -1;
	}

	if (len > wpabuf_tailroom(data->in_buf)) {
		wpa_printf(MSG_DEBUG, "EAP-WSC: Fragment overflow");
		eap_wsc_state(data, FAIL);
		return -1;
	}

	wpabuf_put_data(data->in_buf, buf, len);
	wpa_printf(MSG_DEBUG, "EAP-WSC: Received %lu bytes, waiting for %lu "
		   "bytes more", (unsigned long) len,
		   (unsigned long) wpabuf_tailroom(data->in_buf));

	return 0;
}