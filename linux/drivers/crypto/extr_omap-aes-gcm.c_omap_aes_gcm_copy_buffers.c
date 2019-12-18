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
typedef  int u16 ;
struct scatterlist {int dummy; } ;
struct omap_aes_dev {int flags; int total; int assoc_len; unsigned int authsize; struct scatterlist* out_sg; void* out_sg_len; struct scatterlist* in_sg; void* in_sg_len; struct scatterlist out_sgl; struct scatterlist* orig_out; struct scatterlist* in_sgl; } ;
struct crypto_aead {int dummy; } ;
struct aead_request {int assoclen; int cryptlen; struct scatterlist* dst; struct scatterlist* src; } ;

/* Variables and functions */
 int /*<<< orphan*/  AES_BLOCK_SIZE ; 
 int ALIGN (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FLAGS_ASSOC_DATA_ST_SHIFT ; 
 int FLAGS_ENCRYPT ; 
 int /*<<< orphan*/  FLAGS_IN_DATA_ST_SHIFT ; 
 int /*<<< orphan*/  FLAGS_OUT_DATA_ST_SHIFT ; 
 int FLAGS_RFC4106_GCM ; 
 int OMAP_CRYPTO_COPY_DATA ; 
 int OMAP_CRYPTO_FORCE_COPY ; 
 int OMAP_CRYPTO_FORCE_SINGLE_ENTRY ; 
 int OMAP_CRYPTO_ZERO_BUF ; 
 unsigned int crypto_aead_authsize (struct crypto_aead*) ; 
 struct crypto_aead* crypto_aead_reqtfm (struct aead_request*) ; 
 int /*<<< orphan*/  omap_aes_clear_copy_flags (struct omap_aes_dev*) ; 
 int omap_crypto_align_sg (struct scatterlist**,int,int /*<<< orphan*/ ,struct scatterlist*,int,int /*<<< orphan*/ ,int*) ; 
 void* scatterwalk_ffwd (struct scatterlist*,struct scatterlist*,int) ; 
 int /*<<< orphan*/  sg_init_table (struct scatterlist*,int) ; 
 void* sg_nents_for_len (struct scatterlist*,int) ; 

__attribute__((used)) static int omap_aes_gcm_copy_buffers(struct omap_aes_dev *dd,
				     struct aead_request *req)
{
	int alen, clen, cryptlen, assoclen, ret;
	struct crypto_aead *aead = crypto_aead_reqtfm(req);
	unsigned int authlen = crypto_aead_authsize(aead);
	struct scatterlist *tmp, sg_arr[2];
	int nsg;
	u16 flags;

	assoclen = req->assoclen;
	cryptlen = req->cryptlen;

	if (dd->flags & FLAGS_RFC4106_GCM)
		assoclen -= 8;

	if (!(dd->flags & FLAGS_ENCRYPT))
		cryptlen -= authlen;

	alen = ALIGN(assoclen, AES_BLOCK_SIZE);
	clen = ALIGN(cryptlen, AES_BLOCK_SIZE);

	nsg = !!(assoclen && cryptlen);

	omap_aes_clear_copy_flags(dd);

	sg_init_table(dd->in_sgl, nsg + 1);
	if (assoclen) {
		tmp = req->src;
		ret = omap_crypto_align_sg(&tmp, assoclen,
					   AES_BLOCK_SIZE, dd->in_sgl,
					   OMAP_CRYPTO_COPY_DATA |
					   OMAP_CRYPTO_ZERO_BUF |
					   OMAP_CRYPTO_FORCE_SINGLE_ENTRY,
					   FLAGS_ASSOC_DATA_ST_SHIFT,
					   &dd->flags);
	}

	if (cryptlen) {
		tmp = scatterwalk_ffwd(sg_arr, req->src, req->assoclen);

		ret = omap_crypto_align_sg(&tmp, cryptlen,
					   AES_BLOCK_SIZE, &dd->in_sgl[nsg],
					   OMAP_CRYPTO_COPY_DATA |
					   OMAP_CRYPTO_ZERO_BUF |
					   OMAP_CRYPTO_FORCE_SINGLE_ENTRY,
					   FLAGS_IN_DATA_ST_SHIFT,
					   &dd->flags);
	}

	dd->in_sg = dd->in_sgl;
	dd->total = cryptlen;
	dd->assoc_len = assoclen;
	dd->authsize = authlen;

	dd->out_sg = req->dst;
	dd->orig_out = req->dst;

	dd->out_sg = scatterwalk_ffwd(sg_arr, req->dst, assoclen);

	flags = 0;
	if (req->src == req->dst || dd->out_sg == sg_arr)
		flags |= OMAP_CRYPTO_FORCE_COPY;

	ret = omap_crypto_align_sg(&dd->out_sg, cryptlen,
				   AES_BLOCK_SIZE, &dd->out_sgl,
				   flags,
				   FLAGS_OUT_DATA_ST_SHIFT, &dd->flags);
	if (ret)
		return ret;

	dd->in_sg_len = sg_nents_for_len(dd->in_sg, alen + clen);
	dd->out_sg_len = sg_nents_for_len(dd->out_sg, clen);

	return 0;
}