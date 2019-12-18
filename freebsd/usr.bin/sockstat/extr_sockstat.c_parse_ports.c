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
 int INT_BIT ; 
 int /*<<< orphan*/  SET_PORT (int) ; 
 int /*<<< orphan*/ * calloc (int,int) ; 
 int digittoint (char const) ; 
 int /*<<< orphan*/  err (int,char*) ; 
 int /*<<< orphan*/  errx (int,char*) ; 
 scalar_t__ isdigit (char const) ; 
 int /*<<< orphan*/ * ports ; 

__attribute__((used)) static void
parse_ports(const char *portspec)
{
	const char *p, *q;
	int port, end;

	if (ports == NULL)
		if ((ports = calloc(65536 / INT_BIT, sizeof(int))) == NULL)
			err(1, "calloc()");
	p = portspec;
	while (*p != '\0') {
		if (!isdigit(*p))
			errx(1, "syntax error in port range");
		for (q = p; *q != '\0' && isdigit(*q); ++q)
			/* nothing */ ;
		for (port = 0; p < q; ++p)
			port = port * 10 + digittoint(*p);
		if (port < 0 || port > 65535)
			errx(1, "invalid port number");
		SET_PORT(port);
		switch (*p) {
		case '-':
			++p;
			break;
		case ',':
			++p;
			/* fall through */
		case '\0':
		default:
			continue;
		}
		for (q = p; *q != '\0' && isdigit(*q); ++q)
			/* nothing */ ;
		for (end = 0; p < q; ++p)
			end = end * 10 + digittoint(*p);
		if (end < port || end > 65535)
			errx(1, "invalid port number");
		while (port++ < end)
			SET_PORT(port);
		if (*p == ',')
			++p;
	}
}