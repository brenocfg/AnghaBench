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
struct xxhash64_desc_ctx {int /*<<< orphan*/  xxhstate; } ;
struct shash_desc {int dummy; } ;

/* Variables and functions */
 struct xxhash64_desc_ctx* shash_desc_ctx (struct shash_desc*) ; 
 int /*<<< orphan*/  xxh64_update (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,unsigned int) ; 

__attribute__((used)) static int xxhash64_update(struct shash_desc *desc, const u8 *data,
			 unsigned int length)
{
	struct xxhash64_desc_ctx *dctx = shash_desc_ctx(desc);

	xxh64_update(&dctx->xxhstate, data, length);

	return 0;
}