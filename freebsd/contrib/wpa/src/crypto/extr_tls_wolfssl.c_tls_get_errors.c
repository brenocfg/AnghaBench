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
 int /*<<< orphan*/  MSG_INFO ; 
 int /*<<< orphan*/  wolfSSL_ERR_error_string (unsigned long,int /*<<< orphan*/ *) ; 
 unsigned long wolfSSL_ERR_peek_last_error_line (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 

int tls_get_errors(void *tls_ctx)
{
#ifdef DEBUG_WOLFSSL
#if 0
	unsigned long err;

	err = wolfSSL_ERR_peek_last_error_line(NULL, NULL);
	if (err != 0) {
		wpa_printf(MSG_INFO, "TLS - SSL error: %s",
			   wolfSSL_ERR_error_string(err, NULL));
		return 1;
	}
#endif
#endif /* DEBUG_WOLFSSL */
	return 0;
}