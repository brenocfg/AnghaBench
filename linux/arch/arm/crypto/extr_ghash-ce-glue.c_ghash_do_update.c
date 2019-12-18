#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  char u8 ;
typedef  int /*<<< orphan*/  u64 ;
struct ghash_key {int /*<<< orphan*/  k; } ;
struct TYPE_3__ {int /*<<< orphan*/  a; int /*<<< orphan*/  b; int /*<<< orphan*/  member_1; int /*<<< orphan*/  member_0; } ;
typedef  TYPE_1__ be128 ;

/* Variables and functions */
 int /*<<< orphan*/  GHASH_BLOCK_SIZE ; 
 int /*<<< orphan*/  be64_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpu_to_be64 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  crypto_simd_usable () ; 
 int /*<<< orphan*/  crypto_xor (char*,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gf128mul_lle (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kernel_neon_begin () ; 
 int /*<<< orphan*/  kernel_neon_end () ; 
 scalar_t__ likely (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pmull_ghash_update (int,int /*<<< orphan*/ *,char const*,struct ghash_key*,char const*) ; 

__attribute__((used)) static void ghash_do_update(int blocks, u64 dg[], const char *src,
			    struct ghash_key *key, const char *head)
{
	if (likely(crypto_simd_usable())) {
		kernel_neon_begin();
		pmull_ghash_update(blocks, dg, src, key, head);
		kernel_neon_end();
	} else {
		be128 dst = { cpu_to_be64(dg[1]), cpu_to_be64(dg[0]) };

		do {
			const u8 *in = src;

			if (head) {
				in = head;
				blocks++;
				head = NULL;
			} else {
				src += GHASH_BLOCK_SIZE;
			}

			crypto_xor((u8 *)&dst, in, GHASH_BLOCK_SIZE);
			gf128mul_lle(&dst, &key->k);
		} while (--blocks);

		dg[0] = be64_to_cpu(dst.b);
		dg[1] = be64_to_cpu(dst.a);
	}
}