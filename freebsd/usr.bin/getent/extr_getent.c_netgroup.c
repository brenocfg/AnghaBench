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
 char* NETGROUPPRINT (char*) ; 
 int RV_NOENUM ; 
 int RV_OK ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  endnetgrent () ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  fputs (char*,int /*<<< orphan*/ ) ; 
 scalar_t__ getnetgrent (char**,char**,char**) ; 
 int /*<<< orphan*/  printf (char*,char*,char*,char*) ; 
 int /*<<< orphan*/  putchar (char) ; 
 int /*<<< orphan*/  setnetgrent (char*) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  stdout ; 

__attribute__((used)) static int
netgroup(int argc, char *argv[])
{
	char		*host, *user, *domain;
	int		first;
	int		rv, i;

	assert(argc > 1);
	assert(argv != NULL);

#define NETGROUPPRINT(s)	(((s) != NULL) ? (s) : "")

	rv = RV_OK;
	if (argc == 2) {
		fprintf(stderr, "Enumeration not supported on netgroup\n");
		rv = RV_NOENUM;
	} else {
		for (i = 2; i < argc; i++) {
			setnetgrent(argv[i]);
			first = 1;
			while (getnetgrent(&host, &user, &domain) != 0) {
				if (first) {
					first = 0;
					(void)fputs(argv[i], stdout);
				}
				(void)printf(" (%s,%s,%s)",
				    NETGROUPPRINT(host),
				    NETGROUPPRINT(user),
				    NETGROUPPRINT(domain));
			}
			if (!first)
				(void)putchar('\n');
			endnetgrent();
		}
	}
	return rv;
}