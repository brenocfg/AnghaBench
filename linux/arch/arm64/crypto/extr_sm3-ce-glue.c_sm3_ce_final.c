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
struct shash_desc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  crypto_simd_usable () ; 
 int crypto_sm3_finup (struct shash_desc*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kernel_neon_begin () ; 
 int /*<<< orphan*/  kernel_neon_end () ; 
 int /*<<< orphan*/  sm3_base_do_finalize (struct shash_desc*,int /*<<< orphan*/ ) ; 
 int sm3_base_finish (struct shash_desc*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sm3_ce_transform ; 

__attribute__((used)) static int sm3_ce_final(struct shash_desc *desc, u8 *out)
{
	if (!crypto_simd_usable())
		return crypto_sm3_finup(desc, NULL, 0, out);

	kernel_neon_begin();
	sm3_base_do_finalize(desc, sm3_ce_transform);
	kernel_neon_end();

	return sm3_base_finish(desc, out);
}