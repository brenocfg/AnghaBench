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
struct protosw {int pr_protocol; int pr_type; } ;
struct domain {struct protosw* dom_protoswNPROTOSW; struct protosw* dom_protosw; } ;

/* Variables and functions */
 int SOCK_RAW ; 
 struct domain* pffinddomain (int) ; 

struct protosw *
pffindproto(int family, int protocol, int type)
{
	struct domain *dp;
	struct protosw *pr;
	struct protosw *maybe;

	maybe = NULL;
	if (family == 0)
		return (NULL);

	dp = pffinddomain(family);
	if (dp == NULL)
		return (NULL);

	for (pr = dp->dom_protosw; pr < dp->dom_protoswNPROTOSW; pr++) {
		if ((pr->pr_protocol == protocol) && (pr->pr_type == type))
			return (pr);

		if (type == SOCK_RAW && pr->pr_type == SOCK_RAW &&
		    pr->pr_protocol == 0 && maybe == NULL)
			maybe = pr;
	}
	return (maybe);
}