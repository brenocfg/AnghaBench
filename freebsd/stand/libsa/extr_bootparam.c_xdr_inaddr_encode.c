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
typedef  int /*<<< orphan*/  u_char ;
struct xdr_inaddr {int /*<<< orphan*/ * addr; void* atype; } ;
struct in_addr {int /*<<< orphan*/  s_addr; } ;
typedef  int /*<<< orphan*/  n_long ;
typedef  int /*<<< orphan*/  int32_t ;

/* Variables and functions */
 void* htonl (unsigned int) ; 

int
xdr_inaddr_encode(char **pkt, struct in_addr ia)
{
	struct xdr_inaddr *xi;
	u_char *cp;
	int32_t *ip;
	union {
		n_long l;	/* network order */
		u_char c[4];
	} uia;

	/* The data will be int aligned. */
	xi = (struct xdr_inaddr *) *pkt;
	*pkt += sizeof(*xi);
	xi->atype = htonl(1);
	uia.l = ia.s_addr;
	cp = uia.c;
	ip = xi->addr;
	/*
	 * Note: the htonl() calls below DO NOT
	 * imply that uia.l is in host order.
	 * In fact this needs it in net order.
	 */
	*ip++ = htonl((unsigned int)*cp++);
	*ip++ = htonl((unsigned int)*cp++);
	*ip++ = htonl((unsigned int)*cp++);
	*ip++ = htonl((unsigned int)*cp++);

	return (0);
}