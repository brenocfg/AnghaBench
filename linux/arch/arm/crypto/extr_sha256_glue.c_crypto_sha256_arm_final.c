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
typedef  int /*<<< orphan*/  sha256_block_fn ;

/* Variables and functions */
 int /*<<< orphan*/  sha256_base_do_finalize (struct shash_desc*,int /*<<< orphan*/ *) ; 
 int sha256_base_finish (struct shash_desc*,int /*<<< orphan*/ *) ; 
 scalar_t__ sha256_block_data_order ; 

__attribute__((used)) static int crypto_sha256_arm_final(struct shash_desc *desc, u8 *out)
{
	sha256_base_do_finalize(desc,
				(sha256_block_fn *)sha256_block_data_order);
	return sha256_base_finish(desc, out);
}