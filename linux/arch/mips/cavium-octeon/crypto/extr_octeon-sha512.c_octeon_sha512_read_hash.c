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
struct sha512_state {void** state; } ;

/* Variables and functions */
 void* read_octeon_64bit_hash_sha512 (int) ; 

__attribute__((used)) static void octeon_sha512_read_hash(struct sha512_state *sctx)
{
	sctx->state[0] = read_octeon_64bit_hash_sha512(0);
	sctx->state[1] = read_octeon_64bit_hash_sha512(1);
	sctx->state[2] = read_octeon_64bit_hash_sha512(2);
	sctx->state[3] = read_octeon_64bit_hash_sha512(3);
	sctx->state[4] = read_octeon_64bit_hash_sha512(4);
	sctx->state[5] = read_octeon_64bit_hash_sha512(5);
	sctx->state[6] = read_octeon_64bit_hash_sha512(6);
	sctx->state[7] = read_octeon_64bit_hash_sha512(7);
}