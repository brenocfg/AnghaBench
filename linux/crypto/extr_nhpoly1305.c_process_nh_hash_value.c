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
struct nhpoly1305_state {int /*<<< orphan*/  nh_hash; int /*<<< orphan*/  poly_state; } ;
struct nhpoly1305_key {int /*<<< orphan*/  poly_key; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUILD_BUG_ON (int) ; 
 int NH_HASH_BYTES ; 
 int POLY1305_BLOCK_SIZE ; 
 int /*<<< orphan*/  poly1305_core_blocks (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void process_nh_hash_value(struct nhpoly1305_state *state,
				  const struct nhpoly1305_key *key)
{
	BUILD_BUG_ON(NH_HASH_BYTES % POLY1305_BLOCK_SIZE != 0);

	poly1305_core_blocks(&state->poly_state, &key->poly_key, state->nh_hash,
			     NH_HASH_BYTES / POLY1305_BLOCK_SIZE);
}