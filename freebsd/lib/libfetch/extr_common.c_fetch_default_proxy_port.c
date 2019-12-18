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
 int FTP_DEFAULT_PROXY_PORT ; 
 int HTTP_DEFAULT_PROXY_PORT ; 
 int /*<<< orphan*/  SCHEME_FTP ; 
 int /*<<< orphan*/  SCHEME_HTTP ; 
 scalar_t__ strcmp (char const*,int /*<<< orphan*/ ) ; 

int
fetch_default_proxy_port(const char *scheme)
{
	if (strcmp(scheme, SCHEME_FTP) == 0)
		return (FTP_DEFAULT_PROXY_PORT);
	if (strcmp(scheme, SCHEME_HTTP) == 0)
		return (HTTP_DEFAULT_PROXY_PORT);
	return (0);
}