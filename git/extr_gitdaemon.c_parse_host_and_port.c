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
 int /*<<< orphan*/  die (char*) ; 
 char* strchr (char*,char) ; 
 char* strrchr (char*,char) ; 

__attribute__((used)) static void parse_host_and_port(char *hostport, char **host,
	char **port)
{
	if (*hostport == '[') {
		char *end;

		end = strchr(hostport, ']');
		if (!end)
			die("Invalid request ('[' without ']')");
		*end = '\0';
		*host = hostport + 1;
		if (!end[1])
			*port = NULL;
		else if (end[1] == ':')
			*port = end + 2;
		else
			die("Garbage after end of host part");
	} else {
		*host = hostport;
		*port = strrchr(hostport, ':');
		if (*port) {
			**port = '\0';
			++*port;
		}
	}
}