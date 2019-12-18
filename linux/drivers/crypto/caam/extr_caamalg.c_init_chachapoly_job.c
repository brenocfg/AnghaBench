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
typedef  int u32 ;
struct crypto_aead {int dummy; } ;
struct aead_request {unsigned int assoclen; int /*<<< orphan*/  iv; } ;
struct aead_edesc {int* hw_desc; } ;

/* Variables and functions */
 unsigned int CHACHAPOLY_IV_SIZE ; 
 int /*<<< orphan*/  IMM ; 
 int LDST_CLASS_1_CCB ; 
 int LDST_OFFSET_SHIFT ; 
 int LDST_SRCDST_BYTE_CONTEXT ; 
 int /*<<< orphan*/  REG3 ; 
 int /*<<< orphan*/  ZERO ; 
 int /*<<< orphan*/  append_load_as_imm (int*,int /*<<< orphan*/ ,unsigned int,int) ; 
 int /*<<< orphan*/  append_math_add_imm_u32 (int*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int) ; 
 unsigned int crypto_aead_ivsize (struct crypto_aead*) ; 
 struct crypto_aead* crypto_aead_reqtfm (struct aead_request*) ; 
 int /*<<< orphan*/  init_aead_job (struct aead_request*,struct aead_edesc*,int,int) ; 

__attribute__((used)) static void init_chachapoly_job(struct aead_request *req,
				struct aead_edesc *edesc, bool all_contig,
				bool encrypt)
{
	struct crypto_aead *aead = crypto_aead_reqtfm(req);
	unsigned int ivsize = crypto_aead_ivsize(aead);
	unsigned int assoclen = req->assoclen;
	u32 *desc = edesc->hw_desc;
	u32 ctx_iv_off = 4;

	init_aead_job(req, edesc, all_contig, encrypt);

	if (ivsize != CHACHAPOLY_IV_SIZE) {
		/* IPsec specific: CONTEXT1[223:128] = {NONCE, IV} */
		ctx_iv_off += 4;

		/*
		 * The associated data comes already with the IV but we need
		 * to skip it when we authenticate or encrypt...
		 */
		assoclen -= ivsize;
	}

	append_math_add_imm_u32(desc, REG3, ZERO, IMM, assoclen);

	/*
	 * For IPsec load the IV further in the same register.
	 * For RFC7539 simply load the 12 bytes nonce in a single operation
	 */
	append_load_as_imm(desc, req->iv, ivsize, LDST_CLASS_1_CCB |
			   LDST_SRCDST_BYTE_CONTEXT |
			   ctx_iv_off << LDST_OFFSET_SHIFT);
}