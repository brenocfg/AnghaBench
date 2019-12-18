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
struct tls_in_data {size_t consumed; int /*<<< orphan*/  in_data; } ;
typedef  int /*<<< orphan*/  WOLFSSL ;

/* Variables and functions */
 int /*<<< orphan*/  os_memcpy (char*,size_t,size_t) ; 
 size_t wpabuf_head_u8 (int /*<<< orphan*/ ) ; 
 size_t wpabuf_len (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int wolfssl_receive_cb(WOLFSSL *ssl, char *buf, int sz, void *ctx)
{
	size_t get = sz;
	struct tls_in_data *data = ctx;

	if (!data)
		return -1;

	if (get > (wpabuf_len(data->in_data) - data->consumed))
		get = wpabuf_len(data->in_data) - data->consumed;

	os_memcpy(buf, wpabuf_head_u8(data->in_data) + data->consumed, get);
	data->consumed += get;

	if (get == 0)
		return -2; /* WANT_READ */

	return (int) get;
}