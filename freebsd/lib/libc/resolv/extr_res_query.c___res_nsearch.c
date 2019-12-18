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
typedef  int /*<<< orphan*/  u_char ;
typedef  TYPE_1__* res_state ;
struct TYPE_9__ {int /*<<< orphan*/  rcode; } ;
struct TYPE_8__ {scalar_t__ ndots; int res_h_errno; unsigned int options; scalar_t__ dnsrch; } ;
typedef  TYPE_2__ HEADER ;

/* Variables and functions */
 scalar_t__ ECONNREFUSED ; 
#define  HOST_NOT_FOUND 130 
#define  NO_DATA 129 
 int NS_MAXDNAME ; 
 unsigned int RES_DEFNAMES ; 
 unsigned int RES_DNSRCH ; 
 unsigned int RES_NOTLDQUERY ; 
 int /*<<< orphan*/  RES_SET_H_ERRNO (TYPE_1__*,int const) ; 
 int /*<<< orphan*/  SERVFAIL ; 
#define  TRY_AGAIN 128 
 scalar_t__ errno ; 
 char* res_hostalias (TYPE_1__*,char const*,char*,int) ; 
 int res_nquery (TYPE_1__*,char const*,int,int,int /*<<< orphan*/ *,int) ; 
 int res_nquerydomain (TYPE_1__*,char const*,char const*,int,int,int /*<<< orphan*/ *,int) ; 

int
res_nsearch(res_state statp,
	    const char *name,	/*%< domain name */
	    int class, int type,	/*%< class and type of query */
	    u_char *answer,	/*%< buffer to put answer */
	    int anslen)		/*%< size of answer */
{
	const char *cp, * const *domain;
	HEADER *hp = (HEADER *) answer;
	char tmp[NS_MAXDNAME];
	u_int dots;
	int trailing_dot, ret, saved_herrno;
	int got_nodata = 0, got_servfail = 0, root_on_list = 0;
	int tried_as_is = 0;
	int searched = 0;

	errno = 0;
	RES_SET_H_ERRNO(statp, HOST_NOT_FOUND);  /*%< True if we never query. */
	dots = 0;
	for (cp = name; *cp != '\0'; cp++)
		dots += (*cp == '.');
	trailing_dot = 0;
	if (cp > name && *--cp == '.')
		trailing_dot++;

	/* If there aren't any dots, it could be a user-level alias. */
	if (!dots && (cp = res_hostalias(statp, name, tmp, sizeof tmp))!= NULL)
		return (res_nquery(statp, cp, class, type, answer, anslen));

	/*
	 * If there are enough dots in the name, let's just give it a
	 * try 'as is'. The threshold can be set with the "ndots" option.
	 * Also, query 'as is', if there is a trailing dot in the name.
	 */
	saved_herrno = -1;
	if (dots >= statp->ndots || trailing_dot) {
		ret = res_nquerydomain(statp, name, NULL, class, type,
					 answer, anslen);
		if (ret > 0 || trailing_dot)
			return (ret);
		if (errno == ECONNREFUSED) {
			RES_SET_H_ERRNO(statp, TRY_AGAIN);
			return (-1);
		}
		switch (statp->res_h_errno) {
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
		saved_herrno = statp->res_h_errno;
		tried_as_is++;
	}

	/*
	 * We do at least one level of search if
	 *	- there is no dot and RES_DEFNAME is set, or
	 *	- there is at least one dot, there is no trailing dot,
	 *	  and RES_DNSRCH is set.
	 */
	if ((!dots && (statp->options & RES_DEFNAMES) != 0U) ||
	    (dots && !trailing_dot && (statp->options & RES_DNSRCH) != 0U)) {
		int done = 0;

		for (domain = (const char * const *)statp->dnsrch;
		     *domain && !done;
		     domain++) {
			searched = 1;

			if (domain[0][0] == '\0' ||
			    (domain[0][0] == '.' && domain[0][1] == '\0'))
				root_on_list++;

			if (root_on_list && tried_as_is)
				continue;

			ret = res_nquerydomain(statp, name, *domain,
					       class, type,
					       answer, anslen);
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
				RES_SET_H_ERRNO(statp, TRY_AGAIN);
				return (-1);
			}

			switch (statp->res_h_errno) {
			case NO_DATA:
				got_nodata++;
				/* FALLTHROUGH */
			case HOST_NOT_FOUND:
				/* keep trying */
				break;
			case TRY_AGAIN:
				/*
				 * This can occur due to a server failure
				 * (that is, all listed servers have failed),
				 * or all listed servers have timed out.
				 * ((HEADER *)answer)->rcode may not be set
				 * to SERVFAIL in the case of a timeout.
				 *
				 * Either way we must return TRY_AGAIN in
				 * order to avoid non-deterministic
				 * return codes.
				 * For example, loaded name servers or races
				 * against network startup/validation (dhcp,
				 * ppp, etc) can cause the search to timeout
				 * on one search element, e.g. 'fu.bar.com',
				 * and return a definitive failure on the
				 * next search element, e.g. 'fu.'.
				 */
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

			/* if we got here for some reason other than DNSRCH,
			 * we only wanted one iteration of the loop, so stop.
			 */
			if ((statp->options & RES_DNSRCH) == 0U)
				done++;
		}
	}

	switch (statp->res_h_errno) {
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
	if ((dots || !searched || (statp->options & RES_NOTLDQUERY) == 0U) &&
	    !(tried_as_is || root_on_list)) {
		ret = res_nquerydomain(statp, name, NULL, class, type,
				       answer, anslen);
		if (ret > 0)
			return (ret);
	}

	/* if we got here, we didn't satisfy the search.
	 * if we did an initial full query, return that query's H_ERRNO
	 * (note that we wouldn't be here if that query had succeeded).
	 * else if we ever got a nodata, send that back as the reason.
	 * else send back meaningless H_ERRNO, that being the one from
	 * the last DNSRCH we did.
	 */
giveup:
	if (saved_herrno != -1)
		RES_SET_H_ERRNO(statp, saved_herrno);
	else if (got_nodata)
		RES_SET_H_ERRNO(statp, NO_DATA);
	else if (got_servfail)
		RES_SET_H_ERRNO(statp, TRY_AGAIN);
	return (-1);
}