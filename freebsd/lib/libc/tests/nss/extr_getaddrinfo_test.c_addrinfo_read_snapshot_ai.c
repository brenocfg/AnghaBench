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
struct addrinfo {int ai_flags; int /*<<< orphan*/  ai_addrlen; int /*<<< orphan*/ * ai_addr; int /*<<< orphan*/ * ai_canonname; } ;
typedef  int /*<<< orphan*/  socklen_t ;

/* Variables and functions */
 int /*<<< orphan*/  ATF_REQUIRE (int /*<<< orphan*/ ) ; 
 int addrinfo_read_snapshot_addr (char*,unsigned char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * calloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_addrinfo (struct addrinfo*) ; 
 int /*<<< orphan*/  memset (struct addrinfo*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  strcmp (char*,char*) ; 
 int /*<<< orphan*/ * strdup (char*) ; 
 char* strsep (char**,char*) ; 
 scalar_t__ strtol (char*,char**,int) ; 

__attribute__((used)) static int
addrinfo_read_snapshot_ai(struct addrinfo *ai, char *line)
{
	char *s, *ps, *ts;
	int i, rv, *pi;

	rv = 0;
	i = 0;
	ps = line;
	memset(ai, 0, sizeof(struct addrinfo));
	while ((s = strsep(&ps, " ")) != NULL) {
		switch (i) {
		case 0:
		case 1:
		case 2:
		case 3:
			pi = &ai->ai_flags + i;
			*pi = (int)strtol(s, &ts, 10);
			if (*ts != '\0')
				goto fin;
			break;
		case 4:
			ai->ai_addrlen = (socklen_t)strtol(s, &ts, 10);
			if (*ts != '\0')
				goto fin;
			break;
		case 5:
			if (strcmp(s, "(null)") != 0) {
				ai->ai_canonname = strdup(s);
				ATF_REQUIRE(ai->ai_canonname != NULL);
			}
			break;
		case 6:
			if (strcmp(s, "(null)") != 0) {
				ai->ai_addr = calloc(1, ai->ai_addrlen);
				ATF_REQUIRE(ai->ai_addr != NULL);
				rv = addrinfo_read_snapshot_addr(s,
				    (unsigned char *)ai->ai_addr,
				    ai->ai_addrlen);

				if (rv != 0)
					goto fin;
			}
			break;
		default:
			/* NOTE: should not be reachable */
			rv = -1;
			goto fin;
		}

		++i;
	}

fin:
	if (i != 7 || rv != 0) {
		free_addrinfo(ai);
		ai = NULL;
		return (-1);
	}

	return (0);
}