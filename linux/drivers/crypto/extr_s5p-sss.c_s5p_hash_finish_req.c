#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct s5p_hash_reqctx {int error; TYPE_2__* sg; struct s5p_aes_dev* dd; } ;
struct s5p_aes_dev {int hash_flags; int /*<<< orphan*/  hash_lock; } ;
struct TYPE_4__ {int /*<<< orphan*/  (* complete ) (TYPE_1__*,int) ;} ;
struct ahash_request {TYPE_1__ base; } ;
struct TYPE_5__ {int /*<<< orphan*/  length; } ;

/* Variables and functions */
 int BIT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HASH_FLAGS_BUSY ; 
 int /*<<< orphan*/  HASH_FLAGS_DMA_READY ; 
 int /*<<< orphan*/  HASH_FLAGS_FINAL ; 
 int /*<<< orphan*/  HASH_FLAGS_OUTPUT_READY ; 
 int /*<<< orphan*/  HASH_FLAGS_SGS_ALLOCED ; 
 int /*<<< orphan*/  HASH_FLAGS_SGS_COPIED ; 
 struct s5p_hash_reqctx* ahash_request_ctx (struct ahash_request*) ; 
 int /*<<< orphan*/  free_pages (unsigned long,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_order (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (TYPE_2__*) ; 
 int /*<<< orphan*/  s5p_hash_finish (struct ahash_request*) ; 
 int /*<<< orphan*/  s5p_hash_read_msg (struct ahash_request*) ; 
 scalar_t__ sg_virt (TYPE_2__*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  stub1 (TYPE_1__*,int) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int*) ; 

__attribute__((used)) static void s5p_hash_finish_req(struct ahash_request *req, int err)
{
	struct s5p_hash_reqctx *ctx = ahash_request_ctx(req);
	struct s5p_aes_dev *dd = ctx->dd;
	unsigned long flags;

	if (test_bit(HASH_FLAGS_SGS_COPIED, &dd->hash_flags))
		free_pages((unsigned long)sg_virt(ctx->sg),
			   get_order(ctx->sg->length));

	if (test_bit(HASH_FLAGS_SGS_ALLOCED, &dd->hash_flags))
		kfree(ctx->sg);

	ctx->sg = NULL;
	dd->hash_flags &= ~(BIT(HASH_FLAGS_SGS_ALLOCED) |
			    BIT(HASH_FLAGS_SGS_COPIED));

	if (!err && !ctx->error) {
		s5p_hash_read_msg(req);
		if (test_bit(HASH_FLAGS_FINAL, &dd->hash_flags))
			s5p_hash_finish(req);
	} else {
		ctx->error = true;
	}

	spin_lock_irqsave(&dd->hash_lock, flags);
	dd->hash_flags &= ~(BIT(HASH_FLAGS_BUSY) | BIT(HASH_FLAGS_FINAL) |
			    BIT(HASH_FLAGS_DMA_READY) |
			    BIT(HASH_FLAGS_OUTPUT_READY));
	spin_unlock_irqrestore(&dd->hash_lock, flags);

	if (req->base.complete)
		req->base.complete(&req->base, err);
}