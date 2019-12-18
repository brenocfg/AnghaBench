#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u_short ;
typedef  int /*<<< orphan*/  u_char ;
typedef  TYPE_1__* res_state ;
struct TYPE_3__ {unsigned int options; } ;

/* Variables and functions */
 int /*<<< orphan*/  INT16SZ ; 
 unsigned int RES_DEBUG ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  ns_put16 (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  printf (char*) ; 

int
res_nopt_rdata(res_state statp,
	  int n0,	 	/*%< current offset in buffer */
	  u_char *buf,	 	/*%< buffer to put query */
	  int buflen,		/*%< size of buffer */
	  u_char *rdata,	/*%< ptr to start of opt rdata */
	  u_short code,		/*%< OPTION-CODE */
	  u_short len,		/*%< OPTION-LENGTH */
	  u_char *data)		/*%< OPTION_DATA */
{
	register u_char *cp, *ep;

#ifdef DEBUG
	if ((statp->options & RES_DEBUG) != 0U)
		printf(";; res_nopt_rdata()\n");
#endif

	cp = buf + n0;
	ep = buf + buflen;

	if ((ep - cp) < (4 + len))
		return (-1);

	if (rdata < (buf + 2) || rdata >= ep)
		return (-1);

	ns_put16(code, cp);
	cp += INT16SZ;

	ns_put16(len, cp);
	cp += INT16SZ;

	memcpy(cp, data, len);
	cp += len;

	len = cp - rdata;
	ns_put16(len, rdata - 2);	/* Update RDLEN field */

	return (cp - buf);
}