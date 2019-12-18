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
struct eap_ikev2_data {int /*<<< orphan*/  in_buf; } ;

/* Variables and functions */
 int /*<<< orphan*/  FAIL ; 
 int /*<<< orphan*/  MSG_DEBUG ; 
 int /*<<< orphan*/  eap_ikev2_state (struct eap_ikev2_data*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  wpabuf_put_data (int /*<<< orphan*/ ,int /*<<< orphan*/  const*,size_t) ; 
 size_t wpabuf_tailroom (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int eap_ikev2_process_cont(struct eap_ikev2_data *data,
				  const u8 *buf, size_t len)
{
	/* Process continuation of a pending message */
	if (len > wpabuf_tailroom(data->in_buf)) {
		wpa_printf(MSG_DEBUG, "EAP-IKEV2: Fragment overflow");
		eap_ikev2_state(data, FAIL);
		return -1;
	}

	wpabuf_put_data(data->in_buf, buf, len);
	wpa_printf(MSG_DEBUG, "EAP-IKEV2: Received %lu bytes, waiting "
		   "for %lu bytes more", (unsigned long) len,
		   (unsigned long) wpabuf_tailroom(data->in_buf));

	return 0;
}