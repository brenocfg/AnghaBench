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
struct shash_desc {int dummy; } ;
struct mac_desc_ctx {scalar_t__ len; int /*<<< orphan*/  dg; } ;

/* Variables and functions */
 int /*<<< orphan*/  AES_BLOCK_SIZE ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct mac_desc_ctx* shash_desc_ctx (struct shash_desc*) ; 

__attribute__((used)) static int mac_init(struct shash_desc *desc)
{
	struct mac_desc_ctx *ctx = shash_desc_ctx(desc);

	memset(ctx->dg, 0, AES_BLOCK_SIZE);
	ctx->len = 0;

	return 0;
}