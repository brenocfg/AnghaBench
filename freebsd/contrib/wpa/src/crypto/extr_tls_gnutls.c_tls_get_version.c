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
struct tls_connection {int /*<<< orphan*/  session; } ;
typedef  scalar_t__ gnutls_protocol_t ;

/* Variables and functions */
 scalar_t__ GNUTLS_TLS1_0 ; 
 scalar_t__ GNUTLS_TLS1_1 ; 
 scalar_t__ GNUTLS_TLS1_2 ; 
 scalar_t__ gnutls_protocol_get_version (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  os_strlcpy (char*,char*,size_t) ; 

int tls_get_version(void *ssl_ctx, struct tls_connection *conn,
		    char *buf, size_t buflen)
{
	gnutls_protocol_t ver;

	ver = gnutls_protocol_get_version(conn->session);
	if (ver == GNUTLS_TLS1_0)
		os_strlcpy(buf, "TLSv1", buflen);
	else if (ver == GNUTLS_TLS1_1)
		os_strlcpy(buf, "TLSv1.1", buflen);
	else if (ver == GNUTLS_TLS1_2)
		os_strlcpy(buf, "TLSv1.2", buflen);
	else
		return -1;
	return 0;
}