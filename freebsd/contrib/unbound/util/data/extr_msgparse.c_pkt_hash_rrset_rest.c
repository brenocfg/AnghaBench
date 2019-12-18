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
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  uint16_t ;
typedef  int /*<<< orphan*/  type ;
typedef  int /*<<< orphan*/  hashvalue_type ;
typedef  int /*<<< orphan*/  dclass ;

/* Variables and functions */
 int /*<<< orphan*/  hashlittle (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static hashvalue_type
pkt_hash_rrset_rest(hashvalue_type dname_h, uint16_t type, uint16_t dclass, 
	uint32_t rrset_flags)
{
	/* works together with pkt_hash_rrset_first */
	/* note this MUST be identical to rrset_key_hash in packed_rrset.c */
	hashvalue_type h;
	h = hashlittle(&type, sizeof(type), dname_h);	/* host order */
	h = hashlittle(&dclass, sizeof(dclass), h);	/* netw order */
	h = hashlittle(&rrset_flags, sizeof(uint32_t), h);
	return h;
}