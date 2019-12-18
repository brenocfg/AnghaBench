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
typedef  int u32 ;
typedef  int /*<<< orphan*/  m ;

/* Variables and functions */
 int POLY1305_BLOCK_SIZE ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  poly1305_block_sse2 (int*,int /*<<< orphan*/ *,int const*,int) ; 

__attribute__((used)) static void poly1305_simd_mult(u32 *a, const u32 *b)
{
	u8 m[POLY1305_BLOCK_SIZE];

	memset(m, 0, sizeof(m));
	/* The poly1305 block function adds a hi-bit to the accumulator which
	 * we don't need for key multiplication; compensate for it. */
	a[4] -= 1 << 24;
	poly1305_block_sse2(a, m, b, 1);
}