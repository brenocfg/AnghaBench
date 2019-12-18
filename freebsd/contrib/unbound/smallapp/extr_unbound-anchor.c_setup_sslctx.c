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

/* Variables and functions */
 int /*<<< orphan*/ * SSL_CTX_new (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SSLv23_client_method () ; 
 int /*<<< orphan*/  printf (char*) ; 
 scalar_t__ verb ; 

__attribute__((used)) static SSL_CTX*
setup_sslctx(void)
{
	SSL_CTX* sslctx = SSL_CTX_new(SSLv23_client_method());
	if(!sslctx) {
		if(verb) printf("SSL_CTX_new error\n");
		return NULL;
	}
	return sslctx;
}