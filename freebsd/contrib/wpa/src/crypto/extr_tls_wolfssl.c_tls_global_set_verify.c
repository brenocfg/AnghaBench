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

/* Variables and functions */
 int /*<<< orphan*/  MSG_DEBUG ; 
 int /*<<< orphan*/  SSL_FILETYPE_PEM ; 
 int /*<<< orphan*/  wolfSSL_CTX_LoadCRLBuffer (void*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,int) ; 

int tls_global_set_verify(void *tls_ctx, int check_crl, int strict)
{
	wpa_printf(MSG_DEBUG, "SSL: global set verify: %d", check_crl);

	if (check_crl) {
		/* Hack to Enable CRLs. */
		wolfSSL_CTX_LoadCRLBuffer(tls_ctx, NULL, 0, SSL_FILETYPE_PEM);
	}

	return 0;
}