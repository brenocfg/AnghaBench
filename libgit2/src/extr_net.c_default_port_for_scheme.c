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
 char const* DEFAULT_PORT_GIT ; 
 char const* DEFAULT_PORT_HTTP ; 
 char const* DEFAULT_PORT_HTTPS ; 
 char const* DEFAULT_PORT_SSH ; 
 scalar_t__ strcmp (char const*,char*) ; 

__attribute__((used)) static const char *default_port_for_scheme(const char *scheme)
{
	if (strcmp(scheme, "http") == 0)
		return DEFAULT_PORT_HTTP;
	else if (strcmp(scheme, "https") == 0)
		return DEFAULT_PORT_HTTPS;
	else if (strcmp(scheme, "git") == 0)
		return DEFAULT_PORT_GIT;
	else if (strcmp(scheme, "ssh") == 0)
		return DEFAULT_PORT_SSH;

	return NULL;
}