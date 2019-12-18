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
 int tls_connection_prf (void*,struct tls_connection*,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ *,size_t) ; 

int tls_connection_get_eap_fast_key(void *tls_ctx, struct tls_connection *conn,
				    u8 *out, size_t out_len)
{
	return tls_connection_prf(tls_ctx, conn, "key expansion", NULL, 0,
				  1, 1, out, out_len);
}