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
 int /*<<< orphan*/  wpa_printf (int,char*,char const*,...) ; 

__attribute__((used)) static void tls_show_errors(int level, const char *func, const char *txt)
{
	unsigned long err;

	wpa_printf(level, "OpenSSL: %s - %s %s",
		   func, txt, ERR_error_string(ERR_get_error(), NULL));

	while ((err = ERR_get_error())) {
		wpa_printf(MSG_INFO, "OpenSSL: pending error: %s",
			   ERR_error_string(err, NULL));
	}
}