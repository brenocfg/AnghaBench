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
typedef  scalar_t__ uint8_t ;
struct TYPE_2__ {scalar_t__* dname; } ;
struct ub_packed_rrset_key {TYPE_1__ rk; } ;
struct nsec3_filter {int /*<<< orphan*/  zone; } ;
struct nsec3_cached_hash {size_t b32_len; int /*<<< orphan*/  b32; } ;

/* Variables and functions */
 scalar_t__ label_compare_lower (scalar_t__*,int /*<<< orphan*/ ,size_t) ; 
 scalar_t__ query_dname_compare (scalar_t__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
nsec3_hash_matches_owner(struct nsec3_filter* flt, 
	struct nsec3_cached_hash* hash, struct ub_packed_rrset_key* s)
{
	uint8_t* nm = s->rk.dname;
	/* compare, does hash of name based on params in this NSEC3
	 * match the owner name of this NSEC3? 
	 * name must be: <hashlength>base32 . zone name 
	 * so; first label must not be root label (not zero length),
	 * and match the b32 encoded hash length, 
	 * and the label content match the b32 encoded hash
	 * and the rest must be the zone name.
	 */
	if(hash->b32_len != 0 && (size_t)nm[0] == hash->b32_len &&
		label_compare_lower(nm+1, hash->b32, hash->b32_len) == 0 &&
		query_dname_compare(nm+(size_t)nm[0]+1, flt->zone) == 0) {
		return 1;
	}
	return 0;
}