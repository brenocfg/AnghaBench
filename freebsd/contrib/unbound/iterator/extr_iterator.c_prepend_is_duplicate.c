#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {scalar_t__ type; scalar_t__ rrset_class; scalar_t__ dname_len; int /*<<< orphan*/  dname; } ;
struct ub_packed_rrset_key {TYPE_1__ rk; } ;

/* Variables and functions */
 scalar_t__ query_dname_compare (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
prepend_is_duplicate(struct ub_packed_rrset_key** sets, size_t to,
	struct ub_packed_rrset_key* dup)
{
	size_t i;
	for(i=0; i<to; i++) {
		if(sets[i]->rk.type == dup->rk.type &&
			sets[i]->rk.rrset_class == dup->rk.rrset_class &&
			sets[i]->rk.dname_len == dup->rk.dname_len &&
			query_dname_compare(sets[i]->rk.dname, dup->rk.dname)
			== 0)
			return 1;
	}
	return 0;
}