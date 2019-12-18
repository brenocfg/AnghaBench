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
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_2__ {size_t dname_len; int /*<<< orphan*/ * dname; } ;
struct ub_packed_rrset_key {TYPE_1__ rk; } ;

/* Variables and functions */
 int /*<<< orphan*/  dname_remove_label (int /*<<< orphan*/ **,size_t*) ; 
 int /*<<< orphan*/  nsec3_get_nextowner (struct ub_packed_rrset_key*,int,int /*<<< orphan*/ **,size_t*) ; 
 size_t nsec3_hash_to_b32 (int /*<<< orphan*/ *,size_t,int /*<<< orphan*/ *,size_t,int /*<<< orphan*/ *,size_t) ; 

size_t nsec3_get_nextowner_b32(struct ub_packed_rrset_key* rrset, int r,
	uint8_t* buf, size_t max)
{
	uint8_t* nm, *zone;
	size_t nmlen, zonelen;
	if(!nsec3_get_nextowner(rrset, r, &nm, &nmlen))
		return 0;
	/* append zone name; the owner name must be <b32>.zone */
	zone = rrset->rk.dname;
	zonelen = rrset->rk.dname_len;
	dname_remove_label(&zone, &zonelen);
	return nsec3_hash_to_b32(nm, nmlen, zone, zonelen, buf, max);
}