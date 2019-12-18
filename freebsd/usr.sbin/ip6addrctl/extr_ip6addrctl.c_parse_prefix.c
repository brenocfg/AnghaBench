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
struct in6_addrpolicy {int /*<<< orphan*/  addrmask; int /*<<< orphan*/  addr; } ;
struct addrinfo {int /*<<< orphan*/  ai_addrlen; int /*<<< orphan*/  ai_addr; int /*<<< orphan*/  ai_family; int /*<<< orphan*/  ai_flags; } ;
typedef  int /*<<< orphan*/  hints ;

/* Variables and functions */
 int /*<<< orphan*/  AF_INET6 ; 
 int /*<<< orphan*/  AI_NUMERICHOST ; 
 int atoi (char*) ; 
 int /*<<< orphan*/  errx (int,char*) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  freeaddrinfo (struct addrinfo*) ; 
 int /*<<< orphan*/  gai_strerror (int) ; 
 int getaddrinfo (char*,int /*<<< orphan*/ *,struct addrinfo*,struct addrinfo**) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct addrinfo*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  plen2mask (int /*<<< orphan*/ *,int) ; 
 char* strchr (char*,char) ; 
 char* strdup (char const*) ; 
 int /*<<< orphan*/  warnx (char*,...) ; 

__attribute__((used)) static int
parse_prefix(const char *prefix0, struct in6_addrpolicy *pol)
{
	int e = 0, plen;
	char *prefix, *plenstr;
	struct addrinfo hints, *res;

	if ((prefix = strdup(prefix0)) == NULL)
		errx(1, "strdup failed");

	if ((plenstr = strchr(prefix, '/')) == NULL) {
		e = -1;
		goto end;
	}
	*plenstr = '\0';

	memset(&hints, 0, sizeof(hints));
	hints.ai_flags = AI_NUMERICHOST;
	hints.ai_family = AF_INET6;

	if ((e = getaddrinfo(prefix, NULL, &hints, &res)) != 0) {
		warnx("getaddrinfo failed for %s: %s", prefix,
		      gai_strerror(e));
		goto end;
	}
	memcpy(&pol->addr, res->ai_addr, res->ai_addrlen);
	freeaddrinfo(res);
	plen = atoi(plenstr + 1);
	if (plen < 0 || plen > 128) {
		warnx("invalid prefix length: %d", plen);
		e = -1;
		goto end;
	}
	plen2mask(&pol->addrmask, plen);

  end:
	free(prefix);
	return(e);
}