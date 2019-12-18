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
 scalar_t__ PF_INET6 ; 
 int /*<<< orphan*/  SOCK_RAW ; 
 TYPE_2__ inet6domain ; 
 struct protosw* inet6sw ; 
 int* ip6_protox ; 
 struct protosw* pffindproto (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int
ip6proto_register(short ip6proto)
{
	struct protosw *pr;

	/* Sanity checks. */
	if (ip6proto <= 0 || ip6proto >= IPPROTO_MAX)
		return (EPROTONOSUPPORT);

	/*
	 * The protocol slot must not be occupied by another protocol
	 * already.  An index pointing to IPPROTO_RAW is unused.
	 */
	pr = pffindproto(PF_INET6, IPPROTO_RAW, SOCK_RAW);
	if (pr == NULL)
		return (EPFNOSUPPORT);
	if (ip6_protox[ip6proto] != pr - inet6sw)	/* IPPROTO_RAW */
		return (EEXIST);

	/*
	 * Find the protocol position in inet6sw[] and set the index.
	 */
	for (pr = inet6domain.dom_protosw;
	    pr < inet6domain.dom_protoswNPROTOSW; pr++) {
		if (pr->pr_domain->dom_family == PF_INET6 &&
		    pr->pr_protocol && pr->pr_protocol == ip6proto) {
			ip6_protox[pr->pr_protocol] = pr - inet6sw;
			return (0);
		}
	}
	return (EPROTONOSUPPORT);
}