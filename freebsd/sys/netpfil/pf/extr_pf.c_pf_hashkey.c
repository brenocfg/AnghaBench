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
typedef  int uint32_t ;
struct pf_state_key_cmp {int dummy; } ;
struct pf_state_key {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  V_pf_hashseed ; 
 int murmur3_32_hash32 (int*,int,int /*<<< orphan*/ ) ; 
 int pf_hashmask ; 

__attribute__((used)) static __inline uint32_t
pf_hashkey(struct pf_state_key *sk)
{
	uint32_t h;

	h = murmur3_32_hash32((uint32_t *)sk,
	    sizeof(struct pf_state_key_cmp)/sizeof(uint32_t),
	    V_pf_hashseed);

	return (h & pf_hashmask);
}