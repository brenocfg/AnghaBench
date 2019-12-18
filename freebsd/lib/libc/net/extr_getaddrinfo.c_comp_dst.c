#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_7__ ;
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {scalar_t__ sa_family; } ;
struct ai_order {scalar_t__ aio_dstscope; scalar_t__ aio_srcscope; int aio_srcflag; scalar_t__ aio_matchlen; scalar_t__ aio_initial_sequence; TYPE_7__* aio_ai; TYPE_5__* aio_dstpolicy; TYPE_3__* aio_srcpolicy; TYPE_1__ aio_srcsa; } ;
struct TYPE_14__ {TYPE_6__* ai_addr; } ;
struct TYPE_13__ {scalar_t__ sa_family; } ;
struct TYPE_11__ {scalar_t__ label; scalar_t__ preced; } ;
struct TYPE_12__ {TYPE_4__ pc_policy; } ;
struct TYPE_9__ {scalar_t__ label; } ;
struct TYPE_10__ {TYPE_2__ pc_policy; } ;

/* Variables and functions */
 scalar_t__ AF_INET ; 
 scalar_t__ AF_UNSPEC ; 
 int AIO_SRCFLAG_DEPRECATED ; 

__attribute__((used)) static int
comp_dst(const void *arg1, const void *arg2)
{
	const struct ai_order *dst1 = arg1, *dst2 = arg2;

	/*
	 * Rule 1: Avoid unusable destinations.
	 * XXX: we currently do not consider if an appropriate route exists.
	 */
	if (dst1->aio_srcsa.sa_family != AF_UNSPEC &&
	    dst2->aio_srcsa.sa_family == AF_UNSPEC) {
		return(-1);
	}
	if (dst1->aio_srcsa.sa_family == AF_UNSPEC &&
	    dst2->aio_srcsa.sa_family != AF_UNSPEC) {
		return(1);
	}

	/* Rule 2: Prefer matching scope. */
	if (dst1->aio_dstscope == dst1->aio_srcscope &&
	    dst2->aio_dstscope != dst2->aio_srcscope) {
		return(-1);
	}
	if (dst1->aio_dstscope != dst1->aio_srcscope &&
	    dst2->aio_dstscope == dst2->aio_srcscope) {
		return(1);
	}

	/* Rule 3: Avoid deprecated addresses. */
	if (dst1->aio_srcsa.sa_family != AF_UNSPEC &&
	    dst2->aio_srcsa.sa_family != AF_UNSPEC) {
		if (!(dst1->aio_srcflag & AIO_SRCFLAG_DEPRECATED) &&
		    (dst2->aio_srcflag & AIO_SRCFLAG_DEPRECATED)) {
			return(-1);
		}
		if ((dst1->aio_srcflag & AIO_SRCFLAG_DEPRECATED) &&
		    !(dst2->aio_srcflag & AIO_SRCFLAG_DEPRECATED)) {
			return(1);
		}
	}

	/* Rule 4: Prefer home addresses. */
	/* XXX: not implemented yet */

	/* Rule 5: Prefer matching label. */
#ifdef INET6
	if (dst1->aio_srcpolicy && dst1->aio_dstpolicy &&
	    dst1->aio_srcpolicy->pc_policy.label ==
	    dst1->aio_dstpolicy->pc_policy.label &&
	    (dst2->aio_srcpolicy == NULL || dst2->aio_dstpolicy == NULL ||
	     dst2->aio_srcpolicy->pc_policy.label !=
	     dst2->aio_dstpolicy->pc_policy.label)) {
		return(-1);
	}
	if (dst2->aio_srcpolicy && dst2->aio_dstpolicy &&
	    dst2->aio_srcpolicy->pc_policy.label ==
	    dst2->aio_dstpolicy->pc_policy.label &&
	    (dst1->aio_srcpolicy == NULL || dst1->aio_dstpolicy == NULL ||
	     dst1->aio_srcpolicy->pc_policy.label !=
	     dst1->aio_dstpolicy->pc_policy.label)) {
		return(1);
	}
#endif

	/* Rule 6: Prefer higher precedence. */
#ifdef INET6
	if (dst1->aio_dstpolicy &&
	    (dst2->aio_dstpolicy == NULL ||
	     dst1->aio_dstpolicy->pc_policy.preced >
	     dst2->aio_dstpolicy->pc_policy.preced)) {
		return(-1);
	}
	if (dst2->aio_dstpolicy &&
	    (dst1->aio_dstpolicy == NULL ||
	     dst2->aio_dstpolicy->pc_policy.preced >
	     dst1->aio_dstpolicy->pc_policy.preced)) {
		return(1);
	}
#endif

	/* Rule 7: Prefer native transport. */
	/* XXX: not implemented yet */

	/* Rule 8: Prefer smaller scope. */
	if (dst1->aio_dstscope >= 0 &&
	    dst1->aio_dstscope < dst2->aio_dstscope) {
		return(-1);
	}
	if (dst2->aio_dstscope >= 0 &&
	    dst2->aio_dstscope < dst1->aio_dstscope) {
		return(1);
	}

	/*
	 * Rule 9: Use longest matching prefix.
	 * We compare the match length in a same AF only.
	 */
	if (dst1->aio_ai->ai_addr->sa_family ==
	    dst2->aio_ai->ai_addr->sa_family &&
	    dst1->aio_ai->ai_addr->sa_family != AF_INET) {
		if (dst1->aio_matchlen > dst2->aio_matchlen) {
			return(-1);
		}
		if (dst1->aio_matchlen < dst2->aio_matchlen) {
			return(1);
		}
	}

	/* Rule 10: Otherwise, leave the order unchanged. */

	/* 
	 * Note that qsort is unstable; so, we can't return zero and 
	 * expect the order to be unchanged.
	 * That also means we can't depend on the current position of
	 * dst2 being after dst1.  We must enforce the initial order
	 * with an explicit compare on the original position.
	 * The qsort specification requires that "When the same objects 
	 * (consisting of width bytes, irrespective of their current 
	 * positions in the array) are passed more than once to the 
	 * comparison function, the results shall be consistent with one 
	 * another."  
	 * In other words, If A < B, then we must also return B > A.
	 */
	if (dst2->aio_initial_sequence < dst1->aio_initial_sequence)
		return(1);

	return(-1);
}