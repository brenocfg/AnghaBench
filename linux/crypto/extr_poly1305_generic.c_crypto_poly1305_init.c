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
struct poly1305_desc_ctx {int rset; int sset; scalar_t__ buflen; int /*<<< orphan*/  h; } ;

/* Variables and functions */
 int /*<<< orphan*/  poly1305_core_init (int /*<<< orphan*/ *) ; 
 struct poly1305_desc_ctx* shash_desc_ctx (struct shash_desc*) ; 

int crypto_poly1305_init(struct shash_desc *desc)
{
	struct poly1305_desc_ctx *dctx = shash_desc_ctx(desc);

	poly1305_core_init(&dctx->h);
	dctx->buflen = 0;
	dctx->rset = false;
	dctx->sset = false;

	return 0;
}