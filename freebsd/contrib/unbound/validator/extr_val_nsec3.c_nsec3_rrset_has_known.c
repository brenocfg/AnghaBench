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
struct ub_packed_rrset_key {int dummy; } ;

/* Variables and functions */
 scalar_t__ nsec3_known_algo (struct ub_packed_rrset_key*,int) ; 
 int /*<<< orphan*/  nsec3_unknown_flags (struct ub_packed_rrset_key*,int) ; 
 scalar_t__ rrset_get_count (struct ub_packed_rrset_key*) ; 

__attribute__((used)) static int
nsec3_rrset_has_known(struct ub_packed_rrset_key* s)
{
	int r;
	for(r=0; r < (int)rrset_get_count(s); r++) {
		if(!nsec3_unknown_flags(s, r) && nsec3_known_algo(s, r))
			return 1;
	}
	return 0;
}