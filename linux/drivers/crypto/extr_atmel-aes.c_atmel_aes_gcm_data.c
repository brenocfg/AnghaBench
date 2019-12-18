#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct scatterlist {int dummy; } ;
struct atmel_aes_gcm_ctx {scalar_t__ textlen; int /*<<< orphan*/  dst; int /*<<< orphan*/  src; } ;
struct TYPE_2__ {scalar_t__ has_dualbuff; } ;
struct atmel_aes_dev {scalar_t__ datalen; int data; int (* resume ) (struct atmel_aes_dev*) ;TYPE_1__ caps; int /*<<< orphan*/  areq; int /*<<< orphan*/  ctx; } ;
struct aead_request {int /*<<< orphan*/  assoclen; int /*<<< orphan*/  dst; int /*<<< orphan*/  src; } ;

/* Variables and functions */
 scalar_t__ AES_BLOCK_SIZE ; 
 int /*<<< orphan*/  AES_IDATAR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AES_IER ; 
 int AES_INT_DATARDY ; 
 int /*<<< orphan*/  AES_ISR ; 
 int /*<<< orphan*/  AES_MR ; 
 int AES_MR_DUALBUFF ; 
 int AES_MR_SMOD_IDATAR0 ; 
 int AES_MR_SMOD_MASK ; 
 scalar_t__ ATMEL_AES_DMA_THRESHOLD ; 
 int EINPROGRESS ; 
 struct aead_request* aead_request_cast (int /*<<< orphan*/ ) ; 
 int atmel_aes_cpu_start (struct atmel_aes_dev*,struct scatterlist*,struct scatterlist*,scalar_t__,int (*) (struct atmel_aes_dev*)) ; 
 int atmel_aes_dma_start (struct atmel_aes_dev*,struct scatterlist*,struct scatterlist*,scalar_t__,int (*) (struct atmel_aes_dev*)) ; 
 struct atmel_aes_gcm_ctx* atmel_aes_gcm_ctx_cast (int /*<<< orphan*/ ) ; 
 int atmel_aes_gcm_tag_init (struct atmel_aes_dev*) ; 
 int atmel_aes_read (struct atmel_aes_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  atmel_aes_write (struct atmel_aes_dev*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  atmel_aes_write_block (struct atmel_aes_dev*,int /*<<< orphan*/ ,int) ; 
 struct scatterlist* scatterwalk_ffwd (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int atmel_aes_gcm_data(struct atmel_aes_dev *dd)
{
	struct atmel_aes_gcm_ctx *ctx = atmel_aes_gcm_ctx_cast(dd->ctx);
	struct aead_request *req = aead_request_cast(dd->areq);
	bool use_dma = (ctx->textlen >= ATMEL_AES_DMA_THRESHOLD);
	struct scatterlist *src, *dst;
	u32 isr, mr;

	/* Write AAD first. */
	while (dd->datalen > 0) {
		atmel_aes_write_block(dd, AES_IDATAR(0), dd->data);
		dd->data += 4;
		dd->datalen -= AES_BLOCK_SIZE;

		isr = atmel_aes_read(dd, AES_ISR);
		if (!(isr & AES_INT_DATARDY)) {
			dd->resume = atmel_aes_gcm_data;
			atmel_aes_write(dd, AES_IER, AES_INT_DATARDY);
			return -EINPROGRESS;
		}
	}

	/* GMAC only. */
	if (unlikely(ctx->textlen == 0))
		return atmel_aes_gcm_tag_init(dd);

	/* Prepare src and dst scatter lists to transfer cipher/plain texts */
	src = scatterwalk_ffwd(ctx->src, req->src, req->assoclen);
	dst = ((req->src == req->dst) ? src :
	       scatterwalk_ffwd(ctx->dst, req->dst, req->assoclen));

	if (use_dma) {
		/* Update the Mode Register for DMA transfers. */
		mr = atmel_aes_read(dd, AES_MR);
		mr &= ~(AES_MR_SMOD_MASK | AES_MR_DUALBUFF);
		mr |= AES_MR_SMOD_IDATAR0;
		if (dd->caps.has_dualbuff)
			mr |= AES_MR_DUALBUFF;
		atmel_aes_write(dd, AES_MR, mr);

		return atmel_aes_dma_start(dd, src, dst, ctx->textlen,
					   atmel_aes_gcm_tag_init);
	}

	return atmel_aes_cpu_start(dd, src, dst, ctx->textlen,
				   atmel_aes_gcm_tag_init);
}