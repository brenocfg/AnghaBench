#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct protosw {short pr_protocol; TYPE_1__* pr_domain; } ;
struct TYPE_4__ {struct protosw* dom_protoswNPROTOSW; struct protosw* dom_protosw; } ;
struct TYPE_3__ {scalar_t__ dom_family; } ;

/* Variables and functions */
 int EEXIST ; 
 int EPFNOSUPPORT ; 
 int EPROTONOSUPPORT ; 
 short IPPROTO_MAX ; 
 int /*<<< orphan*/  IPPROTO_RAW ; 
 scalar_t__ PF_INET ; 
 int /*<<< orphan*/  SOCK_RAW ; 
 TYPE_2__ inetdomain ; 
 struct protosw* inetsw ; 
 int* ip_protox ; 
 struct protosw* pffindproto (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int
ipproto_register(short ipproto)
{
	struct protosw *pr;

	/* Sanity checks. */
	if (ipproto <= 0 || ipproto >= IPPROTO_MAX)
		return (EPROTONOSUPPORT);

	/*
	 * The protocol slot must not be occupied by another protocol
	 * already.  An index pointing to IPPROTO_RAW is unused.
	 */
	pr = pffindproto(PF_INET, IPPROTO_RAW, SOCK_RAW);
	if (pr == NULL)
		return (EPFNOSUPPORT);
	if (ip_protox[ipproto] != pr - inetsw)	/* IPPROTO_RAW */
		return (EEXIST);

	/* Find the protocol position in inetsw[] and set the index. */
	for (pr = inetdomain.dom_protosw;
	     pr < inetdomain.dom_protoswNPROTOSW; pr++) {
		if (pr->pr_domain->dom_family == PF_INET &&
		    pr->pr_protocol && pr->pr_protocol == ipproto) {
			ip_protox[pr->pr_protocol] = pr - inetsw;
			return (0);
		}
	}
	return (EPROTONOSUPPORT);
}