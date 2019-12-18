#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u_int ;
struct res_target {scalar_t__ answer; } ;
typedef  TYPE_1__* res_state ;
typedef  int /*<<< orphan*/  abuf ;
struct TYPE_9__ {int /*<<< orphan*/  rcode; } ;
struct TYPE_8__ {scalar_t__ ndots; int res_h_errno; int options; scalar_t__ dnsrch; } ;
typedef  TYPE_2__ HEADER ;

/* Variables and functions */
 scalar_t__ ECONNREFUSED ; 
#define  HOST_NOT_FOUND 130 
 int MAXDNAME ; 
#define  NO_DATA 129 
 int RES_DEFNAMES ; 
 int RES_DNSRCH ; 
 int RES_NOTLDQUERY ; 
 int /*<<< orphan*/  RES_SET_H_ERRNO (TYPE_1__*,int const) ; 
 int /*<<< orphan*/  SERVFAIL ; 
#define  TRY_AGAIN 128 
 scalar_t__ errno ; 
 char* res_hostalias (TYPE_1__*,char const*,char*,int) ; 
 int res_queryN (char const*,struct res_target*,TYPE_1__*) ; 
 int res_querydomainN (char const*,char const*,struct res_target*,TYPE_1__*) ; 

__attribute__((used)) static int
res_searchN(const char *name, struct res_target *target, res_state res)
{
	const char *cp, * const *domain;
	HEADER *hp = (HEADER *)(void *)target->answer;	/*XXX*/
	u_int dots;
	int trailing_dot, ret, saved_herrno;
	int got_nodata = 0, got_servfail = 0, root_on_list = 0;
	int tried_as_is = 0;
	int searched = 0;
	char abuf[MAXDNAME];

	errno = 0;
	RES_SET_H_ERRNO(res, HOST_NOT_FOUND); /* default, if we never query */
	dots = 0;
	for (cp = name; *cp; cp++)
		dots += (*cp == '.');
	trailing_dot = 0;
	if (cp > name && *--cp == '.')
		trailing_dot++;

	/*
	 * if there aren't any dots, it could be a user-level alias
	 */
	if (!dots &&
	    (cp = res_hostalias(res, name, abuf, sizeof(abuf))) != NULL)
		return (res_queryN(cp, target, res));

	/*
	 * If there are enough dots in the name, let's just give it a
	 * try 'as is'. The threshold can be set with the "ndots" option.
	 * Also, query 'as is', if there is a trailing dot in the name.
	 */
	saved_herrno = -1;
	if (dots >= res->ndots || trailing_dot) {
		ret = res_querydomainN(name, NULL, target, res);
		if (ret > 0 || trailing_dot)
			return (ret);
		if (errno == ECONNREFUSED) {
			RES_SET_H_ERRNO(res, TRY_AGAIN);
			return (-1);
		}
		switch (res->res_h_errno) {
		case NO_DATA:
		case HOST_NOT_FOUND:
			break;
		case TRY_AGAIN:
			if (hp->rcode == SERVFAIL)
				break;
			/* FALLTHROUGH */
		default:
			return (-1);
		}
		saved_herrno = res->res_h_errno;
		tried_as_is++;
	}

	/*
	 * We do at least one level of search if
	 *	- there is no dot and RES_DEFNAME is set, or
	 *	- there is at least one dot, there is no trailing dot,
	 *	  and RES_DNSRCH is set.
	 */
	if ((!dots && (res->options & RES_DEFNAMES)) ||
	    (dots && !trailing_dot && (res->options & RES_DNSRCH))) {
		int done = 0;

		for (domain = (const char * const *)res->dnsrch;
		   *domain && !done;
		   domain++) {
			searched = 1;

			if (domain[0][0] == '\0' ||
			    (domain[0][0] == '.' && domain[0][1] == '\0'))
				root_on_list++;

			if (root_on_list && tried_as_is)
				continue;

			ret = res_querydomainN(name, *domain, target, res);
			if (ret > 0)
				return (ret);

			/*
			 * If no server present, give up.
			 * If name isn't found in this domain,
			 * keep trying higher domains in the search list
			 * (if that's enabled).
			 * On a NO_DATA error, keep trying, otherwise
			 * a wildcard entry of another type could keep us
			 * from finding this entry higher in the domain.
			 * If we get some other error (negative answer or
			 * server failure), then stop searching up,
			 * but try the input name below in case it's
			 * fully-qualified.
			 */
			if (errno == ECONNREFUSED) {
				RES_SET_H_ERRNO(res, TRY_AGAIN);
				return (-1);
			}

			switch (res->res_h_errno) {
			case NO_DATA:
				got_nodata++;
				/* FALLTHROUGH */
			case HOST_NOT_FOUND:
				/* keep trying */
				break;
			case TRY_AGAIN:
				got_servfail++;
				if (hp->rcode == SERVFAIL) {
					/* try next search element, if any */
					break;
				}
				/* FALLTHROUGH */
			default:
				/* anything else implies that we're done */
				done++;
			}
			/*
			 * if we got here for some reason other than DNSRCH,
			 * we only wanted one iteration of the loop, so stop.
			 */
			if (!(res->options & RES_DNSRCH))
			        done++;
		}
	}

	switch (res->res_h_errno) {
	case NO_DATA:
	case HOST_NOT_FOUND:
		break;
	case TRY_AGAIN:
		if (hp->rcode == SERVFAIL)
			break;
		/* FALLTHROUGH */
	default:
		goto giveup;
	}

	/*
	 * If the query has not already been tried as is then try it
	 * unless RES_NOTLDQUERY is set and there were no dots.
	 */
	if ((dots || !searched || !(res->options & RES_NOTLDQUERY)) &&
	    !(tried_as_is || root_on_list)) {
		ret = res_querydomainN(name, NULL, target, res);
		if (ret > 0)
			return (ret);
	}

	/*
	 * if we got here, we didn't satisfy the search.
	 * if we did an initial full query, return that query's h_errno
	 * (note that we wouldn't be here if that query had succeeded).
	 * else if we ever got a nodata, send that back as the reason.
	 * else send back meaningless h_errno, that being the one from
	 * the last DNSRCH we did.
	 */
giveup:
	if (saved_herrno != -1)
		RES_SET_H_ERRNO(res, saved_herrno);
	else if (got_nodata)
		RES_SET_H_ERRNO(res, NO_DATA);
	else if (got_servfail)
		RES_SET_H_ERRNO(res, TRY_AGAIN);
	return (-1);
}