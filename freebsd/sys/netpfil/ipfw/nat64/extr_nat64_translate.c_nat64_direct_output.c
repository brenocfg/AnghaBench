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
struct sockaddr {int /*<<< orphan*/  sa_family; } ;
struct nat64_counters {int dummy; } ;
struct mbuf {int dummy; } ;
struct ifnet {int (* if_output ) (struct ifnet*,struct mbuf*,struct sockaddr*,int /*<<< orphan*/ *) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  NAT64STAT_INC (struct nat64_counters*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nat64_log (void*,struct mbuf*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  oerrors ; 
 int stub1 (struct ifnet*,struct mbuf*,struct sockaddr*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
nat64_direct_output(struct ifnet *ifp, struct mbuf *m, struct sockaddr *dst,
    struct nat64_counters *stats, void *logdata)
{
	int error;

	if (logdata != NULL)
		nat64_log(logdata, m, dst->sa_family);
	error = (*ifp->if_output)(ifp, m, dst, NULL);
	if (error != 0)
		NAT64STAT_INC(stats, oerrors);
	return (error);
}