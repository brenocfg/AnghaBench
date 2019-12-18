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
typedef  int u_int8_t ;
struct ip6_hbh {int dummy; } ;
typedef  int socklen_t ;

/* Variables and functions */
#define  IP6OPT_PAD1 129 
#define  IP6OPT_PADN 128 
 int ip6optlen (int*,int*) ; 

int
inet6_opt_next(void *extbuf, socklen_t extlen, int offset, u_int8_t *typep,
	       socklen_t *lenp, void **databufp)
{
	u_int8_t *optp, *lim;
	int optlen;

	/* Validate extlen. XXX: is the variable really necessary?? */
	if (extlen == 0 || (extlen % 8))
		return(-1);
	lim = (u_int8_t *)extbuf + extlen;

	/*
	 * If this is the first time this function called for this options
	 * header, simply return the 1st option.
	 * Otherwise, search the option list for the next option.
	 */
	if (offset == 0) {
		optp = (u_int8_t *)((struct ip6_hbh *)extbuf + 1);
	}
	else
		optp = (u_int8_t *)extbuf + offset;

	/* Find the next option skipping any padding options. */
	while(optp < lim) {
		switch(*optp) {
		case IP6OPT_PAD1:
			optp++;
			break;
		case IP6OPT_PADN:
			if ((optlen = ip6optlen(optp, lim)) == 0)
				goto optend;
			optp += optlen;
			break;
		default:	/* found */
			if ((optlen = ip6optlen(optp, lim)) == 0)
				goto optend;
			*typep = *optp;
			*lenp = optlen - 2;
			*databufp = optp + 2;
			return(optp + optlen - (u_int8_t *)extbuf);
		}
	}

  optend:
	*databufp = NULL; /* for safety */
	return(-1);
}