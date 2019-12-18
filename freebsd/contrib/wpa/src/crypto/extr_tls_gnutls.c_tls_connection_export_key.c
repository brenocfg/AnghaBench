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
struct tls_connection {int /*<<< orphan*/ * session; } ;

/* Variables and functions */
 int gnutls_prf (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,size_t,char*) ; 
 int gnutls_prf_rfc5705 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char const*,size_t,char const*,size_t,char*) ; 
 int /*<<< orphan*/  os_strlen (char const*) ; 

int tls_connection_export_key(void *tls_ctx, struct tls_connection *conn,
			      const char *label, const u8 *context,
			      size_t context_len, u8 *out, size_t out_len)
{
	if (conn == NULL || conn->session == NULL)
		return -1;

#if GNUTLS_VERSION_NUMBER >= 0x030404
	return gnutls_prf_rfc5705(conn->session, os_strlen(label), label,
				  context_len, (const char *) context,
				  out_len, (char *) out);
#else /* 3.4.4 */
	if (context)
		return -1;
	return gnutls_prf(conn->session, os_strlen(label), label,
			  0 /* client_random first */, 0, NULL, out_len,
			  (char *) out);
#endif /* 3.4.4 */
}