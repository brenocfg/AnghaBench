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
typedef  int /*<<< orphan*/  sha512_transform_fn ;
typedef  int /*<<< orphan*/  sha512_block_fn ;

/* Variables and functions */
 int crypto_sha512_finup (struct shash_desc*,int /*<<< orphan*/  const*,unsigned int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  crypto_simd_usable () ; 
 int /*<<< orphan*/  kernel_fpu_begin () ; 
 int /*<<< orphan*/  kernel_fpu_end () ; 
 int /*<<< orphan*/  sha512_base_do_finalize (struct shash_desc*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sha512_base_do_update (struct shash_desc*,int /*<<< orphan*/  const*,unsigned int,int /*<<< orphan*/ *) ; 
 int sha512_base_finish (struct shash_desc*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int sha512_finup(struct shash_desc *desc, const u8 *data,
	      unsigned int len, u8 *out, sha512_transform_fn *sha512_xform)
{
	if (!crypto_simd_usable())
		return crypto_sha512_finup(desc, data, len, out);

	kernel_fpu_begin();
	if (len)
		sha512_base_do_update(desc, data, len,
				      (sha512_block_fn *)sha512_xform);
	sha512_base_do_finalize(desc, (sha512_block_fn *)sha512_xform);
	kernel_fpu_end();

	return sha512_base_finish(desc, out);
}