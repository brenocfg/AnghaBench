#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {unsigned int flags; void* out; void* in; void* csbcpb; } ;
struct TYPE_5__ {unsigned int flags; void* out; void* in; void* csbcpb; } ;
struct nx_crypto_ctx {TYPE_4__* out_sg; TYPE_3__ op_aead; TYPE_4__* in_sg; TYPE_4__* csbcpb_aead; TYPE_1__ op; TYPE_4__* csbcpb; int /*<<< orphan*/  kmem_len; int /*<<< orphan*/  kmem; int /*<<< orphan*/  lock; } ;
struct TYPE_6__ {int /*<<< orphan*/  valid; } ;
struct TYPE_8__ {TYPE_2__ csb; } ;

/* Variables and functions */
 int /*<<< orphan*/  NX_CSB_VALID_BIT ; 
 void* __pa (TYPE_4__*) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

void nx_ctx_init(struct nx_crypto_ctx *nx_ctx, unsigned int function)
{
	spin_lock_init(&nx_ctx->lock);
	memset(nx_ctx->kmem, 0, nx_ctx->kmem_len);
	nx_ctx->csbcpb->csb.valid |= NX_CSB_VALID_BIT;

	nx_ctx->op.flags = function;
	nx_ctx->op.csbcpb = __pa(nx_ctx->csbcpb);
	nx_ctx->op.in = __pa(nx_ctx->in_sg);
	nx_ctx->op.out = __pa(nx_ctx->out_sg);

	if (nx_ctx->csbcpb_aead) {
		nx_ctx->csbcpb_aead->csb.valid |= NX_CSB_VALID_BIT;

		nx_ctx->op_aead.flags = function;
		nx_ctx->op_aead.csbcpb = __pa(nx_ctx->csbcpb_aead);
		nx_ctx->op_aead.in = __pa(nx_ctx->in_sg);
		nx_ctx->op_aead.out = __pa(nx_ctx->out_sg);
	}
}