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
struct netisr_dispatch_table_entry {size_t ndte_policy; char* ndte_policy_str; } ;

/* Variables and functions */
 struct netisr_dispatch_table_entry* netisr_dispatch_table ; 
 size_t nitems (struct netisr_dispatch_table_entry*) ; 
 int /*<<< orphan*/  snprintf (char*,size_t,char*,char const*) ; 

__attribute__((used)) static void
netisr_dispatch_policy_to_str(u_int dispatch_policy, char *buffer,
    u_int buflen)
{
	const struct netisr_dispatch_table_entry *ndtep;
	const char *str;
	u_int i;

	str = "unknown";
	for (i = 0; i < nitems(netisr_dispatch_table); i++) {
		ndtep = &netisr_dispatch_table[i];
		if (ndtep->ndte_policy == dispatch_policy) {
			str = ndtep->ndte_policy_str;
			break;
		}
	}
	snprintf(buffer, buflen, "%s", str);
}