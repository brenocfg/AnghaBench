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
struct tls_connection {int dummy; } ;

/* Variables and functions */
 struct wpabuf* openssl_connection_handshake (struct tls_connection*,struct wpabuf const*,struct wpabuf**) ; 

struct wpabuf *
tls_connection_handshake(void *ssl_ctx, struct tls_connection *conn,
			 const struct wpabuf *in_data,
			 struct wpabuf **appl_data)
{
	return openssl_connection_handshake(conn, in_data, appl_data);
}