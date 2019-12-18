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
typedef  int /*<<< orphan*/  SSL_CTX ;
typedef  int /*<<< orphan*/  SSL ;

/* Variables and functions */
 int /*<<< orphan*/  SSL_CTX_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SSL_free (int /*<<< orphan*/ *) ; 
 scalar_t__ SSL_shutdown (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fd_close (int) ; 

__attribute__((used)) static void
TLS_shutdown(int fd, SSL* ssl, SSL_CTX* sslctx)
{
	/* shutdown the SSL connection nicely */
	if(SSL_shutdown(ssl) == 0) {
		SSL_shutdown(ssl);
	}
	SSL_free(ssl);
	SSL_CTX_free(sslctx);
	fd_close(fd);
}