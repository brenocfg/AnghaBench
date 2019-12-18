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
 int /*<<< orphan*/  PORT_MAX ; 
 int /*<<< orphan*/  PORT_MAX_LEN ; 
 int arc4random () ; 
 char* calloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  err (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  errx (int,char*,char const*,char*) ; 
 char** portlist ; 
 scalar_t__ rflag ; 
 int /*<<< orphan*/  snprintf (char*,int /*<<< orphan*/ ,char*,int) ; 
 char* strchr (char*,char) ; 
 char* strdup (char*) ; 
 int strtonum (char*,int,int /*<<< orphan*/ ,char const**) ; 

void
build_ports(char *p)
{
	const char *errstr;
	char *n;
	int hi, lo, cp;
	int x = 0;

	if ((n = strchr(p, '-')) != NULL) {
		*n = '\0';
		n++;

		/* Make sure the ports are in order: lowest->highest. */
		hi = strtonum(n, 1, PORT_MAX, &errstr);
		if (errstr)
			errx(1, "port number %s: %s", errstr, n);
		lo = strtonum(p, 1, PORT_MAX, &errstr);
		if (errstr)
			errx(1, "port number %s: %s", errstr, p);

		if (lo > hi) {
			cp = hi;
			hi = lo;
			lo = cp;
		}

		/* Load ports sequentially. */
		for (cp = lo; cp <= hi; cp++) {
			portlist[x] = calloc(1, PORT_MAX_LEN);
			if (portlist[x] == NULL)
				err(1, NULL);
			snprintf(portlist[x], PORT_MAX_LEN, "%d", cp);
			x++;
		}

		/* Randomly swap ports. */
		if (rflag) {
			int y;
			char *c;

			for (x = 0; x <= (hi - lo); x++) {
				y = (arc4random() & 0xFFFF) % (hi - lo);
				c = portlist[x];
				portlist[x] = portlist[y];
				portlist[y] = c;
			}
		}
	} else {
		hi = strtonum(p, 1, PORT_MAX, &errstr);
		if (errstr)
			errx(1, "port number %s: %s", errstr, p);
		portlist[0] = strdup(p);
		if (portlist[0] == NULL)
			err(1, NULL);
	}
}