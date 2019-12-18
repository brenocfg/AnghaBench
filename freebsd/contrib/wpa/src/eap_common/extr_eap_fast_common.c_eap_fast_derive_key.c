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
struct tls_connection {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  os_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * os_malloc (size_t) ; 
 scalar_t__ tls_connection_get_eap_fast_key (void*,struct tls_connection*,int /*<<< orphan*/ *,size_t) ; 

u8 * eap_fast_derive_key(void *ssl_ctx, struct tls_connection *conn, size_t len)
{
	u8 *out;

	out = os_malloc(len);
	if (out == NULL)
		return NULL;

	if (tls_connection_get_eap_fast_key(ssl_ctx, conn, out, len)) {
		os_free(out);
		return NULL;
	}

	return out;
}