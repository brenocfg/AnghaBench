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
typedef  size_t u_int ;
struct netisr_dispatch_table_entry {size_t ndte_policy; int /*<<< orphan*/  ndte_policy_str; } ;

/* Variables and functions */
 int EINVAL ; 
 struct netisr_dispatch_table_entry* netisr_dispatch_table ; 
 size_t nitems (struct netisr_dispatch_table_entry*) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char const*) ; 

__attribute__((used)) static int
netisr_dispatch_policy_from_str(const char *str, u_int *dispatch_policyp)
{
	const struct netisr_dispatch_table_entry *ndtep;
	u_int i;

	for (i = 0; i < nitems(netisr_dispatch_table); i++) {
		ndtep = &netisr_dispatch_table[i];
		if (strcmp(ndtep->ndte_policy_str, str) == 0) {
			*dispatch_policyp = ndtep->ndte_policy;
			return (0);
		}
	}
	return (EINVAL);
}