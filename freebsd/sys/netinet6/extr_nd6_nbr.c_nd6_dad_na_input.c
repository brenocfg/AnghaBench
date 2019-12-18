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
struct dadq {int /*<<< orphan*/  dad_na_icount; } ;

/* Variables and functions */
 struct dadq* nd6_dad_find (struct ifaddr*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nd6_dad_rele (struct dadq*) ; 
 int /*<<< orphan*/  panic (char*) ; 

__attribute__((used)) static void
nd6_dad_na_input(struct ifaddr *ifa)
{
	struct dadq *dp;

	if (ifa == NULL)
		panic("ifa == NULL in nd6_dad_na_input");

	dp = nd6_dad_find(ifa, NULL);
	if (dp != NULL) {
		dp->dad_na_icount++;
		nd6_dad_rele(dp);
	}
}