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
struct addrinfo {scalar_t__ ai_next; char* ai_canonname; int /*<<< orphan*/  ai_socktype; int /*<<< orphan*/  ai_family; int /*<<< orphan*/  ai_flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  AI_CANONNAME ; 
 int /*<<< orphan*/  SIGALRM ; 
 int /*<<< orphan*/  SOCK_STREAM ; 
 int /*<<< orphan*/  TIME_LIMIT ; 
 int /*<<< orphan*/  alarm (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cleanup ; 
 int do_protocol (char*,struct addrinfo*) ; 
 int /*<<< orphan*/  family ; 
 int /*<<< orphan*/  freeaddrinfo (struct addrinfo*) ; 
 int /*<<< orphan*/  gai_strerror (int) ; 
 int getaddrinfo (char*,char*,struct addrinfo*,struct addrinfo**) ; 
 int /*<<< orphan*/  printf (char*,char*) ; 
 int /*<<< orphan*/  signal (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 char* strrchr (char*,char) ; 
 int /*<<< orphan*/  trying (struct addrinfo*) ; 
 int /*<<< orphan*/  warnx (char*,char*,int /*<<< orphan*/ ) ; 

void
netfinger(char *name)
{
	int error, multi;
	char *host;
	struct addrinfo *ai, *ai0;
	static struct addrinfo hint;

	host = strrchr(name, '@');
	if (host == NULL)
		return;
	*host++ = '\0';
	signal(SIGALRM, cleanup);
	alarm(TIME_LIMIT);

	hint.ai_flags = AI_CANONNAME;
	hint.ai_family = family;
	hint.ai_socktype = SOCK_STREAM;

	error = getaddrinfo(host, "finger", &hint, &ai0);
	if (error) {
		warnx("%s: %s", host, gai_strerror(error));
		return;
	}

	multi = (ai0->ai_next) != 0;

	/* ai_canonname may not be filled in if the user specified an IP. */
	if (ai0->ai_canonname == 0)
		printf("[%s]\n", host);
	else
		printf("[%s]\n", ai0->ai_canonname);

	for (ai = ai0; ai != NULL; ai = ai->ai_next) {
		if (multi)
			trying(ai);

		error = do_protocol(name, ai);
		if (!error)
			break;
	}
	alarm(0);
	freeaddrinfo(ai0);
}