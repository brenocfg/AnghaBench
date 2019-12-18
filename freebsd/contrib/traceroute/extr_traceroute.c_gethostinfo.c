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
typedef  scalar_t__ u_int32_t ;
struct hostinfo {int n; scalar_t__* addrs; void* name; } ;
struct hostent {scalar_t__ h_addrtype; int h_length; char* h_name; char** h_addr_list; } ;
typedef  int int32_t ;

/* Variables and functions */
 scalar_t__ AF_INET ; 
 int /*<<< orphan*/  Fprintf (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,char*) ; 
 scalar_t__ MAXHOSTNAMELEN ; 
 void* calloc (int,int) ; 
 struct hostent* cap_gethostbyname (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/ * capdns ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  exit (int) ; 
 struct hostent* gethostbyname (char*) ; 
 scalar_t__ inet_addr (char*) ; 
 int /*<<< orphan*/  memcpy (scalar_t__*,char*,int) ; 
 int /*<<< orphan*/  prog ; 
 int /*<<< orphan*/  stderr ; 
 void* strdup (char*) ; 
 char* strerror (int /*<<< orphan*/ ) ; 
 scalar_t__ strlen (char*) ; 

struct hostinfo *
gethostinfo(register char *hostname)
{
	register int n;
	register struct hostent *hp;
	register struct hostinfo *hi;
	register char **p;
	register u_int32_t addr, *ap;

	if (strlen(hostname) >= MAXHOSTNAMELEN) {
		Fprintf(stderr, "%s: hostname \"%.32s...\" is too long\n",
		    prog, hostname);
		exit(1);
	}
	hi = calloc(1, sizeof(*hi));
	if (hi == NULL) {
		Fprintf(stderr, "%s: calloc %s\n", prog, strerror(errno));
		exit(1);
	}
	addr = inet_addr(hostname);
	if ((int32_t)addr != -1) {
		hi->name = strdup(hostname);
		hi->n = 1;
		hi->addrs = calloc(1, sizeof(hi->addrs[0]));
		if (hi->addrs == NULL) {
			Fprintf(stderr, "%s: calloc %s\n",
			    prog, strerror(errno));
			exit(1);
		}
		hi->addrs[0] = addr;
		return (hi);
	}

#ifdef WITH_CASPER
	if (capdns != NULL)
		hp = cap_gethostbyname(capdns, hostname);
	else
#endif
		hp = gethostbyname(hostname);
	if (hp == NULL) {
		Fprintf(stderr, "%s: unknown host %s\n", prog, hostname);
		exit(1);
	}
	if (hp->h_addrtype != AF_INET || hp->h_length != 4) {
		Fprintf(stderr, "%s: bad host %s\n", prog, hostname);
		exit(1);
	}
	hi->name = strdup(hp->h_name);
	for (n = 0, p = hp->h_addr_list; *p != NULL; ++n, ++p)
		continue;
	hi->n = n;
	hi->addrs = calloc(n, sizeof(hi->addrs[0]));
	if (hi->addrs == NULL) {
		Fprintf(stderr, "%s: calloc %s\n", prog, strerror(errno));
		exit(1);
	}
	for (ap = hi->addrs, p = hp->h_addr_list; *p != NULL; ++ap, ++p)
		memcpy(ap, *p, sizeof(*ap));
	return (hi);
}