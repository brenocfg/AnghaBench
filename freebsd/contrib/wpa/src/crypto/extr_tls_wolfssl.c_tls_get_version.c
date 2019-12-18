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
struct tls_connection {int /*<<< orphan*/  ssl; } ;

/* Variables and functions */
 int /*<<< orphan*/  os_strlcpy (char*,char const*,size_t) ; 
 char* wolfSSL_get_version (int /*<<< orphan*/ ) ; 

int tls_get_version(void *ssl_ctx, struct tls_connection *conn,
		    char *buf, size_t buflen)
{
	const char *name;

	if (!conn || !conn->ssl)
		return -1;

	name = wolfSSL_get_version(conn->ssl);
	if (!name)
		return -1;

	os_strlcpy(buf, name, buflen);
	return 0;
}