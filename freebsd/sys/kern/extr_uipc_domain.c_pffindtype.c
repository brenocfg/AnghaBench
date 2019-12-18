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
struct protosw {int pr_type; } ;
struct domain {struct protosw* dom_protoswNPROTOSW; struct protosw* dom_protosw; } ;

/* Variables and functions */
 struct domain* pffinddomain (int) ; 

struct protosw *
pffindtype(int family, int type)
{
	struct domain *dp;
	struct protosw *pr;

	dp = pffinddomain(family);
	if (dp == NULL)
		return (NULL);

	for (pr = dp->dom_protosw; pr < dp->dom_protoswNPROTOSW; pr++)
		if (pr->pr_type && pr->pr_type == type)
			return (pr);
	return (NULL);
}