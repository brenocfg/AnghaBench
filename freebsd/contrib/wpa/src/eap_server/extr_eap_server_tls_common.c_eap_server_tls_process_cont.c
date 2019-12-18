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
struct eap_ssl_data {int /*<<< orphan*/  tls_in; } ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_DEBUG ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  wpabuf_put_data (int /*<<< orphan*/ ,int /*<<< orphan*/  const*,size_t) ; 
 size_t wpabuf_tailroom (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int eap_server_tls_process_cont(struct eap_ssl_data *data,
				       const u8 *buf, size_t len)
{
	/* Process continuation of a pending message */
	if (len > wpabuf_tailroom(data->tls_in)) {
		wpa_printf(MSG_DEBUG, "SSL: Fragment overflow");
		return -1;
	}

	wpabuf_put_data(data->tls_in, buf, len);
	wpa_printf(MSG_DEBUG, "SSL: Received %lu bytes, waiting for %lu "
		   "bytes more", (unsigned long) len,
		   (unsigned long) wpabuf_tailroom(data->tls_in));

	return 0;
}