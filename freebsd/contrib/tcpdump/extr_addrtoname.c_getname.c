#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
typedef  int /*<<< orphan*/  u_char ;
struct hostent {int /*<<< orphan*/  h_name; } ;
struct hnamemem {int addr; char const* name; struct hnamemem* nxt; } ;
struct TYPE_6__ {int /*<<< orphan*/  (* ndo_error ) (TYPE_1__*,char*) ;scalar_t__ ndo_Nflag; int /*<<< orphan*/  ndo_nflag; } ;
typedef  TYPE_1__ netdissect_options ;
typedef  int /*<<< orphan*/  addr ;

/* Variables and functions */
 int /*<<< orphan*/  AF_INET ; 
 int HASHNAMESIZE ; 
 struct hostent* cap_gethostbyaddr (int /*<<< orphan*/ *,char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * capdns ; 
 int f_localnet ; 
 int f_netmask ; 
 struct hostent* gethostbyaddr (char*,int,int /*<<< orphan*/ ) ; 
 struct hnamemem* hnametable ; 
 int /*<<< orphan*/  intoa (int) ; 
 int /*<<< orphan*/  memcpy (int*,int /*<<< orphan*/  const*,int) ; 
 struct hnamemem* newhnamemem (TYPE_1__*) ; 
 char* strchr (char const*,char) ; 
 void* strdup (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  stub2 (TYPE_1__*,char*) ; 

const char *
getname(netdissect_options *ndo, const u_char *ap)
{
	register struct hostent *hp;
	uint32_t addr;
	struct hnamemem *p;

	memcpy(&addr, ap, sizeof(addr));
	p = &hnametable[addr & (HASHNAMESIZE-1)];
	for (; p->nxt; p = p->nxt) {
		if (p->addr == addr)
			return (p->name);
	}
	p->addr = addr;
	p->nxt = newhnamemem(ndo);

	/*
	 * Print names unless:
	 *	(1) -n was given.
	 *      (2) Address is foreign and -f was given. (If -f was not
	 *	    given, f_netmask and f_localnet are 0 and the test
	 *	    evaluates to true)
	 */
	if (!ndo->ndo_nflag &&
	    (addr & f_netmask) == f_localnet) {
#ifdef HAVE_CASPER
		if (capdns != NULL) {
			hp = cap_gethostbyaddr(capdns, (char *)&addr, 4,
			    AF_INET);
		} else
#endif
			hp = gethostbyaddr((char *)&addr, 4, AF_INET);
		if (hp) {
			char *dotp;

			p->name = strdup(hp->h_name);
			if (p->name == NULL)
				(*ndo->ndo_error)(ndo,
						  "getname: strdup(hp->h_name)");
			if (ndo->ndo_Nflag) {
				/* Remove domain qualifications */
				dotp = strchr(p->name, '.');
				if (dotp)
					*dotp = '\0';
			}
			return (p->name);
		}
	}
	p->name = strdup(intoa(addr));
	if (p->name == NULL)
		(*ndo->ndo_error)(ndo, "getname: strdup(intoa(addr))");
	return (p->name);
}