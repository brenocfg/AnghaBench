#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {scalar_t__ icmp_type; int /*<<< orphan*/  icmp_code; } ;
union ad_u {TYPE_1__ icmp; } ;
typedef  int /*<<< orphan*/  u_int ;
struct interface {int dummy; } ;
typedef  int /*<<< orphan*/  naddr ;

/* Variables and functions */
 scalar_t__ ICMP_ROUTERADVERT ; 
 scalar_t__ ICMP_ROUTERSOLICIT ; 
 int /*<<< orphan*/  naddr_ntoa (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  trace_pkt (char*,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  trace_rdisc (char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct interface*,union ad_u*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct interface *		/* 0 if bad */
ck_icmp(const char *act,
	naddr	from,
	struct interface *ifp,
	naddr	to,
	union ad_u *p,
	u_int	len)
{
	const char *type;


	if (p->icmp.icmp_type == ICMP_ROUTERADVERT) {
		type = "advertisement";
	} else if (p->icmp.icmp_type == ICMP_ROUTERSOLICIT) {
		type = "solicitation";
	} else {
		return 0;
	}

	if (p->icmp.icmp_code != 0) {
		trace_pkt("unrecognized ICMP Router %s code=%d from %s to %s",
			  type, p->icmp.icmp_code,
			  naddr_ntoa(from), naddr_ntoa(to));
		return 0;
	}

	trace_rdisc(act, from, to, ifp, p, len);

	if (ifp == NULL)
		trace_pkt("unknown interface for router-discovery %s"
			  " from %s to %s",
			  type, naddr_ntoa(from), naddr_ntoa(to));

	return ifp;
}