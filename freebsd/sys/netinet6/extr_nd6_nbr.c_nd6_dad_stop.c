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
struct ifaddr {int dummy; } ;
struct dadq {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  nd6_dad_del (struct dadq*) ; 
 struct dadq* nd6_dad_find (struct ifaddr*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nd6_dad_rele (struct dadq*) ; 
 int /*<<< orphan*/  nd6_dad_stoptimer (struct dadq*) ; 

void
nd6_dad_stop(struct ifaddr *ifa)
{
	struct dadq *dp;

	dp = nd6_dad_find(ifa, NULL);
	if (!dp) {
		/* DAD wasn't started yet */
		return;
	}

	nd6_dad_stoptimer(dp);
	nd6_dad_del(dp);

	/* Release this function's reference, acquired by nd6_dad_find(). */
	nd6_dad_rele(dp);
}