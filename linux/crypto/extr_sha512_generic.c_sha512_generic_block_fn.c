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
typedef  int /*<<< orphan*/  u8 ;
struct sha512_state {int /*<<< orphan*/  state; } ;

/* Variables and functions */
 int /*<<< orphan*/  SHA512_BLOCK_SIZE ; 
 int /*<<< orphan*/  sha512_transform (int /*<<< orphan*/ ,int /*<<< orphan*/  const*) ; 

__attribute__((used)) static void sha512_generic_block_fn(struct sha512_state *sst, u8 const *src,
				    int blocks)
{
	while (blocks--) {
		sha512_transform(sst->state, src);
		src += SHA512_BLOCK_SIZE;
	}
}