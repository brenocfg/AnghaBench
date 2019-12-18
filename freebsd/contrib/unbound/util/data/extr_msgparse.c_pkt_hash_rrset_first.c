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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  sldns_buffer ;
typedef  int hashvalue_type ;

/* Variables and functions */
 int dname_pkt_hash (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static hashvalue_type
pkt_hash_rrset_first(sldns_buffer* pkt, uint8_t* dname)
{
	/* works together with pkt_hash_rrset_rest */
	/* note this MUST be identical to rrset_key_hash in packed_rrset.c */
	/* this routine handles compressed names */
	hashvalue_type h = 0xab;
	h = dname_pkt_hash(pkt, dname, h);
	return h;
}