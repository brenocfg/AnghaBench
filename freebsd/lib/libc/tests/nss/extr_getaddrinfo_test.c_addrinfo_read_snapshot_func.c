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
struct addrinfo {struct addrinfo* ai_next; } ;

/* Variables and functions */
 int /*<<< orphan*/  ATF_REQUIRE (int /*<<< orphan*/ ) ; 
 int addrinfo_read_snapshot_ai (struct addrinfo*,char*) ; 
 struct addrinfo* calloc (int,int) ; 
 int /*<<< orphan*/  free_addrinfo (struct addrinfo*) ; 
 int /*<<< orphan*/  printf (char*,char*) ; 
 char* strsep (char**,char*) ; 

__attribute__((used)) static int
addrinfo_read_snapshot_func(struct addrinfo *ai, char *line)
{
	struct addrinfo *ai2;
	char *s, *ps;
	int rv;

	printf("1 line read from snapshot:\n%s\n", line);

	rv = 0;
	ps = line;

	s = strsep(&ps, ":");
	if (s == NULL)
		return (-1);

	rv = addrinfo_read_snapshot_ai(ai, s);
	if (rv != 0)
		return (-1);

	ai2 = ai;
	while ((s = strsep(&ps, ":")) != NULL) {
		ai2->ai_next = calloc(1, sizeof(struct addrinfo));
		ATF_REQUIRE(ai2->ai_next != NULL);

		rv = addrinfo_read_snapshot_ai(ai2->ai_next, s);
		if (rv != 0) {
			free_addrinfo(ai);
			ai = NULL;
			return (-1);
		}

		ai2 = ai2->ai_next;
	}

	return (0);
}