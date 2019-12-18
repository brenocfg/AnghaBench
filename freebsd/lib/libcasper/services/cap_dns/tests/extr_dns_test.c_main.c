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
typedef  int /*<<< orphan*/  cap_channel_t ;

/* Variables and functions */
 int AF_INET ; 
 int AF_INET6 ; 
 int /*<<< orphan*/  CHECK (int) ; 
 int /*<<< orphan*/  CHECKX (int /*<<< orphan*/ ) ; 
 scalar_t__ ENOTCAPABLE ; 
 int GETADDRINFO_AF_INET ; 
 int GETADDRINFO_AF_INET6 ; 
 int GETADDRINFO_AF_UNSPEC ; 
 int GETHOSTBYADDR_AF_INET ; 
 int GETHOSTBYADDR_AF_INET6 ; 
 int GETHOSTBYNAME ; 
 int GETHOSTBYNAME2_AF_INET ; 
 int GETHOSTBYNAME2_AF_INET6 ; 
 int /*<<< orphan*/ * cap_clone (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cap_close (int /*<<< orphan*/ *) ; 
 int cap_dns_family_limit (int /*<<< orphan*/ *,int*,int) ; 
 int cap_dns_type_limit (int /*<<< orphan*/ *,char const**,int) ; 
 int /*<<< orphan*/ * cap_init () ; 
 int /*<<< orphan*/ * cap_service_open (int /*<<< orphan*/ *,char*) ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fflush (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*) ; 
 int runtest (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stdout ; 

int
main(void)
{
	cap_channel_t *capcas, *capdns, *origcapdns;
	const char *types[2];
	int families[2];

	printf("1..91\n");
	fflush(stdout);

	capcas = cap_init();
	CHECKX(capcas != NULL);

	origcapdns = capdns = cap_service_open(capcas, "system.dns");
	CHECKX(capdns != NULL);

	cap_close(capcas);

	/* No limits set. */

	CHECK(runtest(capdns) ==
	    (GETHOSTBYNAME | GETHOSTBYNAME2_AF_INET | GETHOSTBYNAME2_AF_INET6 |
	     GETHOSTBYADDR_AF_INET | GETHOSTBYADDR_AF_INET6 |
	     GETADDRINFO_AF_UNSPEC | GETADDRINFO_AF_INET | GETADDRINFO_AF_INET6));

	/*
	 * Allow:
	 * type: NAME, ADDR
	 * family: AF_INET, AF_INET6
	 */

	capdns = cap_clone(origcapdns);
	CHECK(capdns != NULL);

	types[0] = "NAME2ADDR";
	types[1] = "ADDR2NAME";
	CHECK(cap_dns_type_limit(capdns, types, 2) == 0);
	families[0] = AF_INET;
	families[1] = AF_INET6;
	CHECK(cap_dns_family_limit(capdns, families, 2) == 0);

	CHECK(runtest(capdns) ==
	    (GETHOSTBYNAME | GETHOSTBYNAME2_AF_INET | GETHOSTBYNAME2_AF_INET6 |
	     GETHOSTBYADDR_AF_INET | GETHOSTBYADDR_AF_INET6 |
	     GETADDRINFO_AF_INET | GETADDRINFO_AF_INET6));

	cap_close(capdns);

	/*
	 * Allow:
	 * type: NAME
	 * family: AF_INET, AF_INET6
	 */

	capdns = cap_clone(origcapdns);
	CHECK(capdns != NULL);

	types[0] = "NAME2ADDR";
	CHECK(cap_dns_type_limit(capdns, types, 1) == 0);
	types[1] = "ADDR2NAME";
	CHECK(cap_dns_type_limit(capdns, types, 2) == -1 &&
	    errno == ENOTCAPABLE);
	types[0] = "ADDR2NAME";
	CHECK(cap_dns_type_limit(capdns, types, 1) == -1 &&
	    errno == ENOTCAPABLE);
	families[0] = AF_INET;
	families[1] = AF_INET6;
	CHECK(cap_dns_family_limit(capdns, families, 2) == 0);

	CHECK(runtest(capdns) ==
	    (GETHOSTBYNAME | GETHOSTBYNAME2_AF_INET | GETHOSTBYNAME2_AF_INET6 |
	    GETADDRINFO_AF_INET | GETADDRINFO_AF_INET6));

	cap_close(capdns);

	/*
	 * Allow:
	 * type: ADDR
	 * family: AF_INET, AF_INET6
	 */

	capdns = cap_clone(origcapdns);
	CHECK(capdns != NULL);

	types[0] = "ADDR2NAME";
	CHECK(cap_dns_type_limit(capdns, types, 1) == 0);
	types[1] = "NAME2ADDR";
	CHECK(cap_dns_type_limit(capdns, types, 2) == -1 &&
	    errno == ENOTCAPABLE);
	types[0] = "NAME2ADDR";
	CHECK(cap_dns_type_limit(capdns, types, 1) == -1 &&
	    errno == ENOTCAPABLE);
	families[0] = AF_INET;
	families[1] = AF_INET6;
	CHECK(cap_dns_family_limit(capdns, families, 2) == 0);

	CHECK(runtest(capdns) ==
	    (GETHOSTBYADDR_AF_INET | GETHOSTBYADDR_AF_INET6));
	cap_close(capdns);

	/*
	 * Allow:
	 * type: NAME, ADDR
	 * family: AF_INET
	 */

	capdns = cap_clone(origcapdns);
	CHECK(capdns != NULL);

	types[0] = "NAME2ADDR";
	types[1] = "ADDR2NAME";
	CHECK(cap_dns_type_limit(capdns, types, 2) == 0);
	families[0] = AF_INET;
	CHECK(cap_dns_family_limit(capdns, families, 1) == 0);
	families[1] = AF_INET6;
	CHECK(cap_dns_family_limit(capdns, families, 2) == -1 &&
	    errno == ENOTCAPABLE);
	families[0] = AF_INET6;
	CHECK(cap_dns_family_limit(capdns, families, 1) == -1 &&
	    errno == ENOTCAPABLE);

	CHECK(runtest(capdns) ==
	    (GETHOSTBYNAME | GETHOSTBYNAME2_AF_INET | GETHOSTBYADDR_AF_INET |
	    GETADDRINFO_AF_INET));

	cap_close(capdns);

	/*
	 * Allow:
	 * type: NAME, ADDR
	 * family: AF_INET6
	 */

	capdns = cap_clone(origcapdns);
	CHECK(capdns != NULL);

	types[0] = "NAME2ADDR";
	types[1] = "ADDR2NAME";
	CHECK(cap_dns_type_limit(capdns, types, 2) == 0);
	families[0] = AF_INET6;
	CHECK(cap_dns_family_limit(capdns, families, 1) == 0);
	families[1] = AF_INET;
	CHECK(cap_dns_family_limit(capdns, families, 2) == -1 &&
	    errno == ENOTCAPABLE);
	families[0] = AF_INET;
	CHECK(cap_dns_family_limit(capdns, families, 1) == -1 &&
	    errno == ENOTCAPABLE);

	CHECK(runtest(capdns) ==
	    (GETHOSTBYNAME2_AF_INET6 | GETHOSTBYADDR_AF_INET6 |
	    GETADDRINFO_AF_INET6));

	cap_close(capdns);

	/* Below we also test further limiting capability. */

	/*
	 * Allow:
	 * type: NAME
	 * family: AF_INET
	 */

	capdns = cap_clone(origcapdns);
	CHECK(capdns != NULL);

	types[0] = "NAME2ADDR";
	types[1] = "ADDR2NAME";
	CHECK(cap_dns_type_limit(capdns, types, 2) == 0);
	families[0] = AF_INET;
	families[1] = AF_INET6;
	CHECK(cap_dns_family_limit(capdns, families, 2) == 0);
	types[0] = "NAME2ADDR";
	CHECK(cap_dns_type_limit(capdns, types, 1) == 0);
	types[1] = "ADDR2NAME";
	CHECK(cap_dns_type_limit(capdns, types, 2) == -1 &&
	    errno == ENOTCAPABLE);
	types[0] = "ADDR2NAME";
	CHECK(cap_dns_type_limit(capdns, types, 1) == -1 &&
	    errno == ENOTCAPABLE);
	families[0] = AF_INET;
	CHECK(cap_dns_family_limit(capdns, families, 1) == 0);
	families[1] = AF_INET6;
	CHECK(cap_dns_family_limit(capdns, families, 2) == -1 &&
	    errno == ENOTCAPABLE);
	families[0] = AF_INET6;
	CHECK(cap_dns_family_limit(capdns, families, 1) == -1 &&
	    errno == ENOTCAPABLE);

	CHECK(runtest(capdns) ==
	    (GETHOSTBYNAME | GETHOSTBYNAME2_AF_INET | GETADDRINFO_AF_INET));

	cap_close(capdns);

	/*
	 * Allow:
	 * type: NAME
	 * family: AF_INET6
	 */

	capdns = cap_clone(origcapdns);
	CHECK(capdns != NULL);

	types[0] = "NAME2ADDR";
	types[1] = "ADDR2NAME";
	CHECK(cap_dns_type_limit(capdns, types, 2) == 0);
	families[0] = AF_INET;
	families[1] = AF_INET6;
	CHECK(cap_dns_family_limit(capdns, families, 2) == 0);
	types[0] = "NAME2ADDR";
	CHECK(cap_dns_type_limit(capdns, types, 1) == 0);
	types[1] = "ADDR2NAME";
	CHECK(cap_dns_type_limit(capdns, types, 2) == -1 &&
	    errno == ENOTCAPABLE);
	types[0] = "ADDR2NAME";
	CHECK(cap_dns_type_limit(capdns, types, 1) == -1 &&
	    errno == ENOTCAPABLE);
	families[0] = AF_INET6;
	CHECK(cap_dns_family_limit(capdns, families, 1) == 0);
	families[1] = AF_INET;
	CHECK(cap_dns_family_limit(capdns, families, 2) == -1 &&
	    errno == ENOTCAPABLE);
	families[0] = AF_INET;
	CHECK(cap_dns_family_limit(capdns, families, 1) == -1 &&
	    errno == ENOTCAPABLE);

	CHECK(runtest(capdns) ==
	    (GETHOSTBYNAME2_AF_INET6 | GETADDRINFO_AF_INET6));

	cap_close(capdns);

	/*
	 * Allow:
	 * type: ADDR
	 * family: AF_INET
	 */

	capdns = cap_clone(origcapdns);
	CHECK(capdns != NULL);

	types[0] = "NAME2ADDR";
	types[1] = "ADDR2NAME";
	CHECK(cap_dns_type_limit(capdns, types, 2) == 0);
	families[0] = AF_INET;
	families[1] = AF_INET6;
	CHECK(cap_dns_family_limit(capdns, families, 2) == 0);
	types[0] = "ADDR2NAME";
	CHECK(cap_dns_type_limit(capdns, types, 1) == 0);
	types[1] = "NAME2ADDR";
	CHECK(cap_dns_type_limit(capdns, types, 2) == -1 &&
	    errno == ENOTCAPABLE);
	types[0] = "NAME2ADDR";
	CHECK(cap_dns_type_limit(capdns, types, 1) == -1 &&
	    errno == ENOTCAPABLE);
	families[0] = AF_INET;
	CHECK(cap_dns_family_limit(capdns, families, 1) == 0);
	families[1] = AF_INET6;
	CHECK(cap_dns_family_limit(capdns, families, 2) == -1 &&
	    errno == ENOTCAPABLE);
	families[0] = AF_INET6;
	CHECK(cap_dns_family_limit(capdns, families, 1) == -1 &&
	    errno == ENOTCAPABLE);

	CHECK(runtest(capdns) == GETHOSTBYADDR_AF_INET);

	cap_close(capdns);

	/*
	 * Allow:
	 * type: ADDR
	 * family: AF_INET6
	 */

	capdns = cap_clone(origcapdns);
	CHECK(capdns != NULL);

	types[0] = "NAME2ADDR";
	types[1] = "ADDR2NAME";
	CHECK(cap_dns_type_limit(capdns, types, 2) == 0);
	families[0] = AF_INET;
	families[1] = AF_INET6;
	CHECK(cap_dns_family_limit(capdns, families, 2) == 0);
	types[0] = "ADDR2NAME";
	CHECK(cap_dns_type_limit(capdns, types, 1) == 0);
	types[1] = "NAME2ADDR";
	CHECK(cap_dns_type_limit(capdns, types, 2) == -1 &&
	    errno == ENOTCAPABLE);
	types[0] = "NAME2ADDR";
	CHECK(cap_dns_type_limit(capdns, types, 1) == -1 &&
	    errno == ENOTCAPABLE);
	families[0] = AF_INET6;
	CHECK(cap_dns_family_limit(capdns, families, 1) == 0);
	families[1] = AF_INET;
	CHECK(cap_dns_family_limit(capdns, families, 2) == -1 &&
	    errno == ENOTCAPABLE);
	families[0] = AF_INET;
	CHECK(cap_dns_family_limit(capdns, families, 1) == -1 &&
	    errno == ENOTCAPABLE);

	CHECK(runtest(capdns) == GETHOSTBYADDR_AF_INET6);

	cap_close(capdns);

	/* Trying to rise the limits. */

	capdns = cap_clone(origcapdns);
	CHECK(capdns != NULL);

	types[0] = "NAME2ADDR";
	CHECK(cap_dns_type_limit(capdns, types, 1) == 0);
	families[0] = AF_INET;
	CHECK(cap_dns_family_limit(capdns, families, 1) == 0);

	types[0] = "NAME2ADDR";
	types[1] = "ADDR2NAME";
	CHECK(cap_dns_type_limit(capdns, types, 2) == -1 &&
	    errno == ENOTCAPABLE);
	families[0] = AF_INET;
	families[1] = AF_INET6;
	CHECK(cap_dns_family_limit(capdns, families, 2) == -1 &&
	    errno == ENOTCAPABLE);

	types[0] = "ADDR2NAME";
	CHECK(cap_dns_type_limit(capdns, types, 1) == -1 &&
	    errno == ENOTCAPABLE);
	families[0] = AF_INET6;
	CHECK(cap_dns_family_limit(capdns, families, 1) == -1 &&
	    errno == ENOTCAPABLE);

	CHECK(cap_dns_type_limit(capdns, NULL, 0) == -1 &&
	    errno == ENOTCAPABLE);
	CHECK(cap_dns_family_limit(capdns, NULL, 0) == -1 &&
	    errno == ENOTCAPABLE);

	/* Do the limits still hold? */
	CHECK(runtest(capdns) == (GETHOSTBYNAME | GETHOSTBYNAME2_AF_INET |
	    GETADDRINFO_AF_INET));

	cap_close(capdns);

	capdns = cap_clone(origcapdns);
	CHECK(capdns != NULL);

	types[0] = "ADDR2NAME";
	CHECK(cap_dns_type_limit(capdns, types, 1) == 0);
	families[0] = AF_INET6;
	CHECK(cap_dns_family_limit(capdns, families, 1) == 0);

	types[0] = "NAME2ADDR";
	types[1] = "ADDR2NAME";
	CHECK(cap_dns_type_limit(capdns, types, 2) == -1 &&
	    errno == ENOTCAPABLE);
	families[0] = AF_INET;
	families[1] = AF_INET6;
	CHECK(cap_dns_family_limit(capdns, families, 2) == -1 &&
	    errno == ENOTCAPABLE);

	types[0] = "NAME2ADDR";
	CHECK(cap_dns_type_limit(capdns, types, 1) == -1 &&
	    errno == ENOTCAPABLE);
	families[0] = AF_INET;
	CHECK(cap_dns_family_limit(capdns, families, 1) == -1 &&
	    errno == ENOTCAPABLE);

	CHECK(cap_dns_type_limit(capdns, NULL, 0) == -1 &&
	    errno == ENOTCAPABLE);
	CHECK(cap_dns_family_limit(capdns, NULL, 0) == -1 &&
	    errno == ENOTCAPABLE);

	/* Do the limits still hold? */
	CHECK(runtest(capdns) == GETHOSTBYADDR_AF_INET6);

	cap_close(capdns);

	cap_close(origcapdns);

	exit(0);
}