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
typedef  scalar_t__ u32 ;
struct sec4_sg_entry {int dummy; } ;
struct crypto_aead {int dummy; } ;
struct caam_ctx {int authsize; int sh_desc_enc_dma; int sh_desc_dec_dma; scalar_t__* sh_desc_dec; scalar_t__* sh_desc_enc; } ;
struct aead_request {scalar_t__ src; scalar_t__ dst; scalar_t__ cryptlen; scalar_t__ assoclen; } ;
struct aead_edesc {int sec4_sg_dma; int mapped_dst_nents; scalar_t__ mapped_src_nents; scalar_t__* hw_desc; } ;
typedef  int dma_addr_t ;

/* Variables and functions */
 int HDR_REVERSE ; 
 int HDR_SHARE_DEFER ; 
 scalar_t__ LDST_SGF ; 
 int /*<<< orphan*/  append_seq_in_ptr (scalar_t__*,int,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  append_seq_out_ptr (scalar_t__*,int,scalar_t__,scalar_t__) ; 
 struct caam_ctx* crypto_aead_ctx (struct crypto_aead*) ; 
 struct crypto_aead* crypto_aead_reqtfm (struct aead_request*) ; 
 int desc_len (scalar_t__*) ; 
 int /*<<< orphan*/  init_job_desc_shared (scalar_t__*,int,int,int) ; 
 int sg_dma_address (scalar_t__) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static void init_aead_job(struct aead_request *req,
			  struct aead_edesc *edesc,
			  bool all_contig, bool encrypt)
{
	struct crypto_aead *aead = crypto_aead_reqtfm(req);
	struct caam_ctx *ctx = crypto_aead_ctx(aead);
	int authsize = ctx->authsize;
	u32 *desc = edesc->hw_desc;
	u32 out_options, in_options;
	dma_addr_t dst_dma, src_dma;
	int len, sec4_sg_index = 0;
	dma_addr_t ptr;
	u32 *sh_desc;

	sh_desc = encrypt ? ctx->sh_desc_enc : ctx->sh_desc_dec;
	ptr = encrypt ? ctx->sh_desc_enc_dma : ctx->sh_desc_dec_dma;

	len = desc_len(sh_desc);
	init_job_desc_shared(desc, ptr, len, HDR_SHARE_DEFER | HDR_REVERSE);

	if (all_contig) {
		src_dma = edesc->mapped_src_nents ? sg_dma_address(req->src) :
						    0;
		in_options = 0;
	} else {
		src_dma = edesc->sec4_sg_dma;
		sec4_sg_index += edesc->mapped_src_nents;
		in_options = LDST_SGF;
	}

	append_seq_in_ptr(desc, src_dma, req->assoclen + req->cryptlen,
			  in_options);

	dst_dma = src_dma;
	out_options = in_options;

	if (unlikely(req->src != req->dst)) {
		if (!edesc->mapped_dst_nents) {
			dst_dma = 0;
			out_options = 0;
		} else if (edesc->mapped_dst_nents == 1) {
			dst_dma = sg_dma_address(req->dst);
			out_options = 0;
		} else {
			dst_dma = edesc->sec4_sg_dma +
				  sec4_sg_index *
				  sizeof(struct sec4_sg_entry);
			out_options = LDST_SGF;
		}
	}

	if (encrypt)
		append_seq_out_ptr(desc, dst_dma,
				   req->assoclen + req->cryptlen + authsize,
				   out_options);
	else
		append_seq_out_ptr(desc, dst_dma,
				   req->assoclen + req->cryptlen - authsize,
				   out_options);
}