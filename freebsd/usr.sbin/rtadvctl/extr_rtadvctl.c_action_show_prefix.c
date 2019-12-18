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
struct timespec {long tv_sec; } ;
struct prefix {int pfx_prefixlen; int pfx_origin; scalar_t__ pfx_validlifetime; scalar_t__ pfx_vltimeexpire; scalar_t__ pfx_preflifetime; scalar_t__ pfx_pltimeexpire; scalar_t__ pfx_timer; scalar_t__ pfx_autoconfflg; scalar_t__ pfx_onlinkflg; int /*<<< orphan*/  pfx_prefix; } ;
typedef  int /*<<< orphan*/  ntopbuf ;

/* Variables and functions */
 int /*<<< orphan*/  AF_INET6 ; 
 int /*<<< orphan*/  CLOCK_MONOTONIC_FAST ; 
 int INET6_ADDRSTRLEN ; 
 scalar_t__ ND6_INFINITE_LIFETIME ; 
#define  PREFIX_FROM_CONFIG 130 
#define  PREFIX_FROM_DYNAMIC 129 
#define  PREFIX_FROM_KERNEL 128 
 int SSBUFLEN ; 
 int /*<<< orphan*/  clock_gettime (int /*<<< orphan*/ ,struct timespec*) ; 
 char* inet_ntop (int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 struct timespec* rtadvd_timer_rest (scalar_t__) ; 
 char* sec2str (scalar_t__,char*) ; 

__attribute__((used)) static int
action_show_prefix(struct prefix *pfx)
{
	char ntopbuf[INET6_ADDRSTRLEN];
	char ssbuf[SSBUFLEN];
	struct timespec now;

	clock_gettime(CLOCK_MONOTONIC_FAST, &now);
	printf("\t  %s/%d", inet_ntop(AF_INET6, &pfx->pfx_prefix,
		ntopbuf, sizeof(ntopbuf)), pfx->pfx_prefixlen);

	printf(" (");
	switch (pfx->pfx_origin) {
	case PREFIX_FROM_KERNEL:
		printf("KERNEL");
		break;
	case PREFIX_FROM_CONFIG:
		printf("CONFIG");
		break;
	case PREFIX_FROM_DYNAMIC:
		printf("DYNAMIC");
		break;
	}

	printf(",");

	printf(" vltime=%s",
	    (pfx->pfx_validlifetime == ND6_INFINITE_LIFETIME) ?
	    "infinity" : sec2str(pfx->pfx_validlifetime, ssbuf));

	if (pfx->pfx_vltimeexpire > 0)
		printf("(expire: %s)",
		    ((long)pfx->pfx_vltimeexpire > now.tv_sec) ?
		    sec2str(pfx->pfx_vltimeexpire - now.tv_sec, ssbuf) :
		    "0");

	printf(",");

	printf(" pltime=%s",
	    (pfx->pfx_preflifetime == ND6_INFINITE_LIFETIME) ?
	    "infinity" : sec2str(pfx->pfx_preflifetime, ssbuf));

	if (pfx->pfx_pltimeexpire > 0)
		printf("(expire %s)",
		    ((long)pfx->pfx_pltimeexpire > now.tv_sec) ?
		    sec2str(pfx->pfx_pltimeexpire - now.tv_sec, ssbuf) :
		    "0");

	printf(",");

	printf(" flags=");
	if (pfx->pfx_onlinkflg || pfx->pfx_autoconfflg) {
		printf("%s", pfx->pfx_onlinkflg ? "L" : "");
		printf("%s", pfx->pfx_autoconfflg ? "A" : "");
	} else
		printf("<none>");

	if (pfx->pfx_timer) {
		struct timespec *rest;

		rest = rtadvd_timer_rest(pfx->pfx_timer);
		if (rest) { /* XXX: what if not? */
			printf(" expire=%s", sec2str(rest->tv_sec, ssbuf));
		}
	}

	printf(")\n");

	return (0);
}