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
 int asprintf (char**,char*,char*,char*,char*,char*,int /*<<< orphan*/ ,char*,char*) ; 
 scalar_t__ env_HTTP_PROXY ; 
 int /*<<< orphan*/  env_HTTP_USER_AGENT ; 
 int /*<<< orphan*/  err (int,char*) ; 
 char* proxyauth ; 

__attribute__((used)) static int
makerequest(char ** buf, char * path, char * server, int connclose)
{
	int buflen;

	buflen = asprintf(buf,
	    "GET %s%s/%s HTTP/1.1\r\n"
	    "Host: %s\r\n"
	    "User-Agent: %s\r\n"
	    "%s"
	    "%s"
	    "\r\n",
	    env_HTTP_PROXY ? "http://" : "",
	    env_HTTP_PROXY ? server : "",
	    path, server, env_HTTP_USER_AGENT,
	    proxyauth ? proxyauth : "",
	    connclose ? "Connection: Close\r\n" : "Connection: Keep-Alive\r\n");
	if (buflen == -1)
		err(1, "asprintf");
	return(buflen);
}