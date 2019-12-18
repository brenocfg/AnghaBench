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
struct sun4i_req_ctx {int byte_count; int len; int /*<<< orphan*/ * hash; int /*<<< orphan*/  buf; } ;
struct md5_state {int byte_count; int /*<<< orphan*/ * hash; int /*<<< orphan*/  block; } ;
struct ahash_request {int dummy; } ;

/* Variables and functions */
 struct sun4i_req_ctx* ahash_request_ctx (struct ahash_request*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  sun4i_hash_init (struct ahash_request*) ; 

int sun4i_hash_import_md5(struct ahash_request *areq, const void *in)
{
	struct sun4i_req_ctx *op = ahash_request_ctx(areq);
	const struct md5_state *ictx = in;
	int i;

	sun4i_hash_init(areq);

	op->byte_count = ictx->byte_count & ~0x3F;
	op->len = ictx->byte_count & 0x3F;

	memcpy(op->buf, ictx->block, op->len);

	for (i = 0; i < 4; i++)
		op->hash[i] = ictx->hash[i];

	return 0;
}