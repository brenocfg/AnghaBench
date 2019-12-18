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
struct addrinfo {int /*<<< orphan*/  ai_flags; int /*<<< orphan*/  ai_socktype; int /*<<< orphan*/  ai_family; } ;
typedef  int /*<<< orphan*/  hints ;

/* Variables and functions */
 int /*<<< orphan*/  AI_PASSIVE ; 
 int /*<<< orphan*/  PF_UNSPEC ; 
 int /*<<< orphan*/  SOCK_STREAM ; 
 int /*<<< orphan*/  free (char*) ; 
 int getaddrinfo (char*,char const*,struct addrinfo*,struct addrinfo**) ; 
 int /*<<< orphan*/  memset (struct addrinfo*,int /*<<< orphan*/ ,int) ; 
 char* strdup (char*) ; 
 char* strsep (char**,char*) ; 

__attribute__((used)) static int
parse_addr_port(char *arg, const char *def_port, struct addrinfo **ai)
{
	struct addrinfo hints;
	char *str, *addr, *ch;
	const char *port;
	int error, colons = 0;

	str = arg = strdup(arg);
	if (arg[0] == '[') {
		/*
		 * IPv6 address in square brackets, perhaps with port.
		 */
		arg++;
		addr = strsep(&arg, "]");
		if (arg == NULL) {
			free(str);
			return (1);
		}
		if (arg[0] == '\0') {
			port = def_port;
		} else if (arg[0] == ':') {
			port = arg + 1;
		} else {
			free(str);
			return (1);
		}
	} else {
		/*
		 * Either IPv6 address without brackets - and without
		 * a port - or IPv4 address.  Just count the colons.
		 */
		for (ch = arg; *ch != '\0'; ch++) {
			if (*ch == ':')
				colons++;
		}
		if (colons > 1) {
			addr = arg;
			port = def_port;
		} else {
			addr = strsep(&arg, ":");
			if (arg == NULL)
				port = def_port;
			else
				port = arg;
		}
	}

	memset(&hints, 0, sizeof(hints));
	hints.ai_family = PF_UNSPEC;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_flags = AI_PASSIVE;
	error = getaddrinfo(addr, port, &hints, ai);
	free(str);
	return ((error != 0) ? 1 : 0);
}