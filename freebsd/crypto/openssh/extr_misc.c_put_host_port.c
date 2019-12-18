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
typedef  scalar_t__ u_short ;

/* Variables and functions */
 scalar_t__ SSH_DEFAULT_PORT ; 
 scalar_t__ asprintf (char**,char*,char const*,int) ; 
 int /*<<< orphan*/  debug3 (char*,char*) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  fatal (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strerror (int /*<<< orphan*/ ) ; 
 char* xstrdup (char const*) ; 

char *
put_host_port(const char *host, u_short port)
{
	char *hoststr;

	if (port == 0 || port == SSH_DEFAULT_PORT)
		return(xstrdup(host));
	if (asprintf(&hoststr, "[%s]:%d", host, (int)port) < 0)
		fatal("put_host_port: asprintf: %s", strerror(errno));
	debug3("put_host_port: %s", hoststr);
	return hoststr;
}