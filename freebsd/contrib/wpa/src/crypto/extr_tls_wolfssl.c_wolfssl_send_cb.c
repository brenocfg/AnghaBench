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
struct wpabuf {int dummy; } ;
struct tls_out_data {int /*<<< orphan*/  out_data; } ;
typedef  int /*<<< orphan*/  WOLFSSL ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_DEBUG ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,int) ; 
 struct wpabuf* wpabuf_alloc_copy (char*,int) ; 
 int /*<<< orphan*/  wpabuf_concat (int /*<<< orphan*/ ,struct wpabuf*) ; 

__attribute__((used)) static int wolfssl_send_cb(WOLFSSL *ssl, char *buf, int sz, void *ctx)
{
	struct wpabuf *tmp;
	struct tls_out_data *data = ctx;

	if (!data)
		return -1;

	wpa_printf(MSG_DEBUG, "SSL: adding %d bytes", sz);

	tmp = wpabuf_alloc_copy(buf, sz);
	if (!tmp)
		return -1;
	data->out_data = wpabuf_concat(data->out_data, tmp);
	if (!data->out_data)
		return -1;

	return sz;
}