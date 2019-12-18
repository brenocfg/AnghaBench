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
typedef  void* u64 ;
typedef  int /*<<< orphan*/  u32 ;
struct sha1_state {int /*<<< orphan*/ * state; } ;

/* Variables and functions */
 int /*<<< orphan*/  memzero_explicit (void**,int) ; 
 void* read_octeon_64bit_hash_dword (int) ; 

__attribute__((used)) static void octeon_sha1_read_hash(struct sha1_state *sctx)
{
	u64 *hash = (u64 *)sctx->state;
	union {
		u32 word[2];
		u64 dword;
	} hash_tail;

	hash[0]		= read_octeon_64bit_hash_dword(0);
	hash[1]		= read_octeon_64bit_hash_dword(1);
	hash_tail.dword	= read_octeon_64bit_hash_dword(2);
	sctx->state[4]	= hash_tail.word[0];
	memzero_explicit(&hash_tail.dword, sizeof(hash_tail.dword));
}