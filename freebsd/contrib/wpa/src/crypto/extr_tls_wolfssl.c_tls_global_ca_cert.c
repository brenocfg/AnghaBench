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
typedef  int /*<<< orphan*/  WOLFSSL_CTX ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_DEBUG ; 
 int /*<<< orphan*/  MSG_WARNING ; 
 int wolfSSL_CTX_load_verify_locations (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int tls_global_ca_cert(void *ssl_ctx, const char *ca_cert)
{
	WOLFSSL_CTX *ctx = ssl_ctx;

	if (ca_cert) {
		if (wolfSSL_CTX_load_verify_locations(ctx, ca_cert, NULL) != 1)
		{
			wpa_printf(MSG_WARNING,
				   "Failed to load root certificates");
			return -1;
		}

		wpa_printf(MSG_DEBUG,
			   "TLS: Trusted root certificate(s) loaded");
	}

	return 0;
}