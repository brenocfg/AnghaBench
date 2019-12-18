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
typedef  int /*<<< orphan*/  u_short ;
struct bsm_domain {int bd_local_domain; } ;

/* Variables and functions */
 struct bsm_domain* bsm_lookup_bsm_domain (int /*<<< orphan*/ ) ; 

int
au_bsm_to_domain(u_short bsm_domain, int *local_domainp)
{
	const struct bsm_domain *bstp;

	bstp = bsm_lookup_bsm_domain(bsm_domain);
	if (bstp == NULL || bstp->bd_local_domain)
		return (-1);
	*local_domainp = bstp->bd_local_domain;
	return (0);
}