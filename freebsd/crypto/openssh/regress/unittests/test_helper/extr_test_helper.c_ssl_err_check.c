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
 char* ERR_error_string (long,int /*<<< orphan*/ *) ; 
 long ERR_get_error () ; 
 int /*<<< orphan*/  abort () ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char const*,int,char*) ; 
 int /*<<< orphan*/  stderr ; 

void
ssl_err_check(const char *file, int line)
{
	long openssl_error = ERR_get_error();

	if (openssl_error == 0)
		return;

	fprintf(stderr, "\n%s:%d: uncaught OpenSSL error: %s",
	    file, line, ERR_error_string(openssl_error, NULL));
	abort();
}