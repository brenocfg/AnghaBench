#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  icmp_so_rsvd; } ;
struct TYPE_7__ {int icmp_ad_num; int /*<<< orphan*/  icmp_ad_asize; TYPE_2__* icmp_ad_info; int /*<<< orphan*/  icmp_ad_life; } ;
struct TYPE_5__ {scalar_t__ icmp_type; } ;
union ad_u {TYPE_4__ so; TYPE_3__ ad; TYPE_1__ icmp; } ;
typedef  int u_int ;
struct interface {char* int_name; } ;
typedef  int /*<<< orphan*/  naddr ;
typedef  int /*<<< orphan*/  n_long ;
struct TYPE_6__ {int /*<<< orphan*/  icmp_ad_addr; } ;

/* Variables and functions */
 scalar_t__ ICMP_ROUTERADVERT ; 
 int /*<<< orphan*/  TRACECONTENTS ; 
 int /*<<< orphan*/  TRACEPACKETS ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*,char const*,...) ; 
 int /*<<< orphan*/  fputc (char,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * ftrace ; 
 int /*<<< orphan*/  lastlog () ; 
 char* naddr_ntoa (int /*<<< orphan*/ ) ; 
 scalar_t__ ntohl (int /*<<< orphan*/ ) ; 
 int ntohs (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  trace_act (char*,char const*,char*,char*,char*,int) ; 

__attribute__((used)) static void
trace_rdisc(const char	*act,
	    naddr	from,
	    naddr	to,
	    struct interface *ifp,
	    union ad_u	*p,
	    u_int	len)
{
	int i;
	n_long *wp, *lim;


	if (!TRACEPACKETS || ftrace == NULL)
		return;

	lastlog();

	if (p->icmp.icmp_type == ICMP_ROUTERADVERT) {
		(void)fprintf(ftrace, "%s Router Ad"
			      " from %s to %s via %s life=%d\n",
			      act, naddr_ntoa(from), naddr_ntoa(to),
			      ifp ? ifp->int_name : "?",
			      ntohs(p->ad.icmp_ad_life));
		if (!TRACECONTENTS)
			return;

		wp = &p->ad.icmp_ad_info[0].icmp_ad_addr;
		lim = &wp[(len - sizeof(p->ad)) / sizeof(*wp)];
		for (i = 0; i < p->ad.icmp_ad_num && wp <= lim; i++) {
			(void)fprintf(ftrace, "\t%s preference=%d",
				      naddr_ntoa(wp[0]), (int)ntohl(wp[1]));
			wp += p->ad.icmp_ad_asize;
		}
		(void)fputc('\n',ftrace);

	} else {
		trace_act("%s Router Solic. from %s to %s via %s value=%#x",
			  act, naddr_ntoa(from), naddr_ntoa(to),
			  ifp ? ifp->int_name : "?",
			  (int)ntohl(p->so.icmp_so_rsvd));
	}
}