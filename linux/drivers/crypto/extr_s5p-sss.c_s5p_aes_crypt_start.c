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
typedef  int /*<<< orphan*/  u8 ;
typedef  int u32 ;
struct s5p_aes_dev {int busy; int /*<<< orphan*/  lock; int /*<<< orphan*/  sg_dst; int /*<<< orphan*/  sg_src; TYPE_1__* ctx; struct ablkcipher_request* req; } ;
struct ablkcipher_request {int /*<<< orphan*/ * info; } ;
struct TYPE_2__ {scalar_t__ keylen; int /*<<< orphan*/  aes_key; } ;

/* Variables and functions */
 int /*<<< orphan*/  AES_CONTROL ; 
 scalar_t__ AES_KEYSIZE_192 ; 
 scalar_t__ AES_KEYSIZE_256 ; 
 int /*<<< orphan*/  FCFIFOCTRL ; 
 int /*<<< orphan*/  FCINTENCLR ; 
 int /*<<< orphan*/  FCINTENSET ; 
 unsigned long FLAGS_AES_CBC ; 
 unsigned long FLAGS_AES_CTR ; 
 unsigned long FLAGS_AES_DECRYPT ; 
 unsigned long FLAGS_AES_MODE_MASK ; 
 int SSS_AES_BYTESWAP_CNT ; 
 int SSS_AES_BYTESWAP_DI ; 
 int SSS_AES_BYTESWAP_DO ; 
 int SSS_AES_BYTESWAP_IV ; 
 int SSS_AES_BYTESWAP_KEY ; 
 int SSS_AES_CHAIN_MODE_CBC ; 
 int SSS_AES_CHAIN_MODE_CTR ; 
 int SSS_AES_FIFO_MODE ; 
 int SSS_AES_KEY_CHANGE_MODE ; 
 int SSS_AES_KEY_SIZE_192 ; 
 int SSS_AES_KEY_SIZE_256 ; 
 int SSS_AES_MODE_DECRYPT ; 
 int /*<<< orphan*/  SSS_AES_WRITE (struct s5p_aes_dev*,int /*<<< orphan*/ ,int) ; 
 int SSS_FCINTENCLR_BRDMAINTENCLR ; 
 int SSS_FCINTENCLR_BTDMAINTENCLR ; 
 int SSS_FCINTENSET_BRDMAINTENSET ; 
 int SSS_FCINTENSET_BTDMAINTENSET ; 
 int /*<<< orphan*/  SSS_WRITE (struct s5p_aes_dev*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  s5p_aes_complete (struct ablkcipher_request*,int) ; 
 int /*<<< orphan*/  s5p_set_aes (struct s5p_aes_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  s5p_set_dma_indata (struct s5p_aes_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  s5p_set_dma_outdata (struct s5p_aes_dev*,int /*<<< orphan*/ ) ; 
 int s5p_set_indata_start (struct s5p_aes_dev*,struct ablkcipher_request*) ; 
 int s5p_set_outdata_start (struct s5p_aes_dev*,struct ablkcipher_request*) ; 
 int /*<<< orphan*/  s5p_sg_done (struct s5p_aes_dev*) ; 
 int /*<<< orphan*/  s5p_unset_indata (struct s5p_aes_dev*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void s5p_aes_crypt_start(struct s5p_aes_dev *dev, unsigned long mode)
{
	struct ablkcipher_request *req = dev->req;
	u32 aes_control;
	unsigned long flags;
	int err;
	u8 *iv, *ctr;

	/* This sets bit [13:12] to 00, which selects 128-bit counter */
	aes_control = SSS_AES_KEY_CHANGE_MODE;
	if (mode & FLAGS_AES_DECRYPT)
		aes_control |= SSS_AES_MODE_DECRYPT;

	if ((mode & FLAGS_AES_MODE_MASK) == FLAGS_AES_CBC) {
		aes_control |= SSS_AES_CHAIN_MODE_CBC;
		iv = req->info;
		ctr = NULL;
	} else if ((mode & FLAGS_AES_MODE_MASK) == FLAGS_AES_CTR) {
		aes_control |= SSS_AES_CHAIN_MODE_CTR;
		iv = NULL;
		ctr = req->info;
	} else {
		iv = NULL; /* AES_ECB */
		ctr = NULL;
	}

	if (dev->ctx->keylen == AES_KEYSIZE_192)
		aes_control |= SSS_AES_KEY_SIZE_192;
	else if (dev->ctx->keylen == AES_KEYSIZE_256)
		aes_control |= SSS_AES_KEY_SIZE_256;

	aes_control |= SSS_AES_FIFO_MODE;

	/* as a variant it is possible to use byte swapping on DMA side */
	aes_control |= SSS_AES_BYTESWAP_DI
		    |  SSS_AES_BYTESWAP_DO
		    |  SSS_AES_BYTESWAP_IV
		    |  SSS_AES_BYTESWAP_KEY
		    |  SSS_AES_BYTESWAP_CNT;

	spin_lock_irqsave(&dev->lock, flags);

	SSS_WRITE(dev, FCINTENCLR,
		  SSS_FCINTENCLR_BTDMAINTENCLR | SSS_FCINTENCLR_BRDMAINTENCLR);
	SSS_WRITE(dev, FCFIFOCTRL, 0x00);

	err = s5p_set_indata_start(dev, req);
	if (err)
		goto indata_error;

	err = s5p_set_outdata_start(dev, req);
	if (err)
		goto outdata_error;

	SSS_AES_WRITE(dev, AES_CONTROL, aes_control);
	s5p_set_aes(dev, dev->ctx->aes_key, iv, ctr, dev->ctx->keylen);

	s5p_set_dma_indata(dev,  dev->sg_src);
	s5p_set_dma_outdata(dev, dev->sg_dst);

	SSS_WRITE(dev, FCINTENSET,
		  SSS_FCINTENSET_BTDMAINTENSET | SSS_FCINTENSET_BRDMAINTENSET);

	spin_unlock_irqrestore(&dev->lock, flags);

	return;

outdata_error:
	s5p_unset_indata(dev);

indata_error:
	s5p_sg_done(dev);
	dev->busy = false;
	spin_unlock_irqrestore(&dev->lock, flags);
	s5p_aes_complete(req, err);
}