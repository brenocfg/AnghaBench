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
typedef  scalar_t__ u_short ;
struct bsm_domain {scalar_t__ bd_bsm_domain; } ;

/* Variables and functions */
 struct bsm_domain const* bsm_domains ; 
 int bsm_domains_count ; 

__attribute__((used)) static const struct bsm_domain *
bsm_lookup_bsm_domain(u_short bsm_domain)
{
	int i;

	for (i = 0; i < bsm_domains_count; i++) {
		if (bsm_domains[i].bd_bsm_domain == bsm_domain)
			return (&bsm_domains[i]);
	}
	return (NULL);
}