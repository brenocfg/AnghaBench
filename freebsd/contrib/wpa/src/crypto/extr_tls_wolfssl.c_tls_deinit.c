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
struct tls_context {int dummy; } ;
typedef  int /*<<< orphan*/  WOLFSSL_CTX ;

/* Variables and functions */
 int /*<<< orphan*/  os_free (struct tls_context*) ; 
 struct tls_context* tls_global ; 
 scalar_t__ tls_ref_count ; 
 int /*<<< orphan*/  wolfSSL_CTX_free (int /*<<< orphan*/ *) ; 
 struct tls_context* wolfSSL_CTX_get_ex_data (void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wolfSSL_Cleanup () ; 

void tls_deinit(void *ssl_ctx)
{
	struct tls_context *context = wolfSSL_CTX_get_ex_data(ssl_ctx, 0);

	if (context != tls_global)
		os_free(context);

	wolfSSL_CTX_free((WOLFSSL_CTX *) ssl_ctx);

	tls_ref_count--;
	if (tls_ref_count == 0) {
		wolfSSL_Cleanup();
		os_free(tls_global);
		tls_global = NULL;
	}
}