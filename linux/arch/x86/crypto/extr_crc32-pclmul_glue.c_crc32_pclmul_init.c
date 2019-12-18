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
typedef  int /*<<< orphan*/  u32 ;
struct shash_desc {int /*<<< orphan*/  tfm; } ;

/* Variables and functions */
 int /*<<< orphan*/ * crypto_shash_ctx (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * shash_desc_ctx (struct shash_desc*) ; 

__attribute__((used)) static int crc32_pclmul_init(struct shash_desc *desc)
{
	u32 *mctx = crypto_shash_ctx(desc->tfm);
	u32 *crcp = shash_desc_ctx(desc);

	*crcp = *mctx;

	return 0;
}