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
 int /*<<< orphan*/  ERR_error_string (unsigned long,int /*<<< orphan*/ *) ; 
 unsigned long ERR_get_error () ; 
 int /*<<< orphan*/  MSG_INFO ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 

int tls_get_errors(void *ssl_ctx)
{
	int count = 0;
	unsigned long err;

	while ((err = ERR_get_error())) {
		wpa_printf(MSG_INFO, "TLS - SSL error: %s",
			   ERR_error_string(err, NULL));
		count++;
	}

	return count;
}