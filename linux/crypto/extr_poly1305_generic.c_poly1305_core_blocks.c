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
struct poly1305_state {int dummy; } ;
struct poly1305_key {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  poly1305_blocks_internal (struct poly1305_state*,struct poly1305_key const*,void const*,unsigned int,int) ; 

void poly1305_core_blocks(struct poly1305_state *state,
			  const struct poly1305_key *key,
			  const void *src, unsigned int nblocks)
{
	poly1305_blocks_internal(state, key, src, nblocks, 1 << 24);
}