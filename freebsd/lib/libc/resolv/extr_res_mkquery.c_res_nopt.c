#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  unsigned int u_int16_t ;
typedef  int /*<<< orphan*/  u_char ;
typedef  TYPE_1__* res_state ;
struct TYPE_5__ {int /*<<< orphan*/  arcount; } ;
struct TYPE_4__ {unsigned int options; } ;
typedef  TYPE_2__ HEADER ;

/* Variables and functions */
 int /*<<< orphan*/  INT16SZ ; 
 scalar_t__ NOERROR ; 
 unsigned int NS_OPT_DNSSEC_OK ; 
 unsigned int RES_DEBUG ; 
 int RES_USE_DNSSEC ; 
 int RRFIXEDSZ ; 
 int /*<<< orphan*/  htons (scalar_t__) ; 
 int /*<<< orphan*/  ns_put16 (unsigned int,int /*<<< orphan*/ *) ; 
 unsigned int ns_t_opt ; 
 scalar_t__ ntohs (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*) ; 

int
res_nopt(res_state statp,
	 int n0,		/*%< current offset in buffer */
	 u_char *buf,		/*%< buffer to put query */
	 int buflen,		/*%< size of buffer */
	 int anslen)		/*%< UDP answer buffer size */
{
	HEADER *hp;
	u_char *cp, *ep;
	u_int16_t flags = 0;

#ifdef DEBUG
	if ((statp->options & RES_DEBUG) != 0U)
		printf(";; res_nopt()\n");
#endif

	hp = (HEADER *) buf;
	cp = buf + n0;
	ep = buf + buflen;

	if ((ep - cp) < 1 + RRFIXEDSZ)
		return (-1);

	*cp++ = 0;				/*%< "." */
	ns_put16(ns_t_opt, cp);			/*%< TYPE */
	cp += INT16SZ;
	if (anslen > 0xffff)
		anslen = 0xffff;		/* limit to 16bit value */
	ns_put16(anslen & 0xffff, cp);		/*%< CLASS = UDP payload size */
	cp += INT16SZ;
	*cp++ = NOERROR;			/*%< extended RCODE */
	*cp++ = 0;				/*%< EDNS version */

	if (statp->options & RES_USE_DNSSEC) {
#ifdef DEBUG
		if (statp->options & RES_DEBUG)
			printf(";; res_opt()... ENDS0 DNSSEC\n");
#endif
		flags |= NS_OPT_DNSSEC_OK;
	}
	ns_put16(flags, cp);
	cp += INT16SZ;

	ns_put16(0U, cp);			/*%< RDLEN */
	cp += INT16SZ;

	hp->arcount = htons(ntohs(hp->arcount) + 1);

	return (cp - buf);
}