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
struct sha512_state {int /*<<< orphan*/ * state; } ;

/* Variables and functions */
 int /*<<< orphan*/  write_octeon_64bit_hash_sha512 (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void octeon_sha512_store_hash(struct sha512_state *sctx)
{
	write_octeon_64bit_hash_sha512(sctx->state[0], 0);
	write_octeon_64bit_hash_sha512(sctx->state[1], 1);
	write_octeon_64bit_hash_sha512(sctx->state[2], 2);
	write_octeon_64bit_hash_sha512(sctx->state[3], 3);
	write_octeon_64bit_hash_sha512(sctx->state[4], 4);
	write_octeon_64bit_hash_sha512(sctx->state[5], 5);
	write_octeon_64bit_hash_sha512(sctx->state[6], 6);
	write_octeon_64bit_hash_sha512(sctx->state[7], 7);
}