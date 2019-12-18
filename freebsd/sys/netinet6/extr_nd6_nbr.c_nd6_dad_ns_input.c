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
struct nd_opt_nonce {int dummy; } ;
struct ifaddr {int dummy; } ;
struct dadq {int /*<<< orphan*/  dad_ns_icount; } ;

/* Variables and functions */
 scalar_t__ V_dad_enhanced ; 
 struct dadq* nd6_dad_find (struct ifaddr*,struct nd_opt_nonce*) ; 
 int /*<<< orphan*/  nd6_dad_rele (struct dadq*) ; 
 int /*<<< orphan*/  panic (char*) ; 

__attribute__((used)) static void
nd6_dad_ns_input(struct ifaddr *ifa, struct nd_opt_nonce *ndopt_nonce)
{
	struct dadq *dp;

	if (ifa == NULL)
		panic("ifa == NULL in nd6_dad_ns_input");

	/* Ignore Nonce option when Enhanced DAD is disabled. */
	if (V_dad_enhanced == 0)
		ndopt_nonce = NULL;
	dp = nd6_dad_find(ifa, ndopt_nonce);
	if (dp == NULL)
		return;

	dp->dad_ns_icount++;
	nd6_dad_rele(dp);
}