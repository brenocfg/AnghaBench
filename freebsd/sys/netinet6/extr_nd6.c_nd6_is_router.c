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
#define  ND_NEIGHBOR_SOLICIT 131 
#define  ND_REDIRECT 130 
 int ND_REDIRECT_ROUTER ; 
#define  ND_ROUTER_ADVERT 129 
#define  ND_ROUTER_SOLICIT 128 

__attribute__((used)) static int
nd6_is_router(int type, int code, int is_new, int old_addr, int new_addr,
    int ln_router)
{

	/*
	 * ICMP6 type dependent behavior.
	 *
	 * NS: clear IsRouter if new entry
	 * RS: clear IsRouter
	 * RA: set IsRouter if there's lladdr
	 * redir: clear IsRouter if new entry
	 *
	 * RA case, (1):
	 * The spec says that we must set IsRouter in the following cases:
	 * - If lladdr exist, set IsRouter.  This means (1-5).
	 * - If it is old entry (!newentry), set IsRouter.  This means (7).
	 * So, based on the spec, in (1-5) and (7) cases we must set IsRouter.
	 * A quetion arises for (1) case.  (1) case has no lladdr in the
	 * neighbor cache, this is similar to (6).
	 * This case is rare but we figured that we MUST NOT set IsRouter.
	 *
	 *   is_new  old_addr new_addr 	    NS  RS  RA	redir
	 *							D R
	 *	0	n	n	(1)	c   ?     s
	 *	0	y	n	(2)	c   s     s
	 *	0	n	y	(3)	c   s     s
	 *	0	y	y	(4)	c   s     s
	 *	0	y	y	(5)	c   s     s
	 *	1	--	n	(6) c	c	c s
	 *	1	--	y	(7) c	c   s	c s
	 *
	 *					(c=clear s=set)
	 */
	switch (type & 0xff) {
	case ND_NEIGHBOR_SOLICIT:
		/*
		 * New entry must have is_router flag cleared.
		 */
		if (is_new)					/* (6-7) */
			ln_router = 0;
		break;
	case ND_REDIRECT:
		/*
		 * If the icmp is a redirect to a better router, always set the
		 * is_router flag.  Otherwise, if the entry is newly created,
		 * clear the flag.  [RFC 2461, sec 8.3]
		 */
		if (code == ND_REDIRECT_ROUTER)
			ln_router = 1;
		else {
			if (is_new)				/* (6-7) */
				ln_router = 0;
		}
		break;
	case ND_ROUTER_SOLICIT:
		/*
		 * is_router flag must always be cleared.
		 */
		ln_router = 0;
		break;
	case ND_ROUTER_ADVERT:
		/*
		 * Mark an entry with lladdr as a router.
		 */
		if ((!is_new && (old_addr || new_addr)) ||	/* (2-5) */
		    (is_new && new_addr)) {			/* (7) */
			ln_router = 1;
		}
		break;
	}

	return (ln_router);
}