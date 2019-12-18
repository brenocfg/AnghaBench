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
struct tls_connection {int /*<<< orphan*/  ssl; } ;

/* Variables and functions */
 int SSL_export_keying_material (int /*<<< orphan*/ ,int /*<<< orphan*/ *,size_t,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/  const*,size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  os_strlen (char const*) ; 

int tls_connection_export_key(void *tls_ctx, struct tls_connection *conn,
			      const char *label, const u8 *context,
			      size_t context_len, u8 *out, size_t out_len)
{
	if (!conn ||
	    SSL_export_keying_material(conn->ssl, out, out_len, label,
				       os_strlen(label), context, context_len,
				       context != NULL) != 1)
		return -1;
	return 0;
}