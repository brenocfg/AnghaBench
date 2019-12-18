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
struct alginfo {int algtype; int /*<<< orphan*/  keylen; int /*<<< orphan*/  key_dma; int /*<<< orphan*/  key_virt; } ;

/* Variables and functions */
 int /*<<< orphan*/  CAAM_CMD_SZ ; 
 int CLASS_1 ; 
 int FIFOLDST_VLF ; 
 int FIFOLD_CLASS_CLASS1 ; 
 int FIFOLD_TYPE_LAST1 ; 
 int FIFOLD_TYPE_MSG ; 
 int FIFOST_TYPE_KEY_KEK ; 
 int HDR_SAVECTX ; 
 int HDR_SHARE_SERIAL ; 
 int JUMP_COND_SHRD ; 
 int JUMP_TEST_ALL ; 
 int KEY_DEST_CLASS_REG ; 
 int KEY_ENC ; 
 int LDST_CLASS_1_CCB ; 
 int LDST_SRCDST_BYTE_CONTEXT ; 
 int OP_ALG_AS_INIT ; 
 int OP_ALG_AS_INITFINAL ; 
 int OP_ALG_ENCRYPT ; 
 int /*<<< orphan*/  REG0 ; 
 int /*<<< orphan*/  SEQINLEN ; 
 int /*<<< orphan*/  VARSEQINLEN ; 
 int /*<<< orphan*/  append_fifo_store (int* const,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int* append_jump (int* const,int) ; 
 int /*<<< orphan*/  append_key (int* const,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  append_key_as_imm (int* const,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  append_math_add (int* const,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  append_operation (int* const,int) ; 
 int /*<<< orphan*/  append_seq_fifo_load (int* const,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  append_seq_load (int* const,int,int) ; 
 int /*<<< orphan*/  append_seq_store (int* const,int,int) ; 
 int /*<<< orphan*/  init_sh_desc (int* const,int) ; 
 scalar_t__ is_xcbc_aes (int) ; 
 int /*<<< orphan*/  set_jump_tgt_here (int* const,int*) ; 

void cnstr_shdsc_sk_hash(u32 * const desc, struct alginfo *adata, u32 state,
			 int digestsize, int ctx_len)
{
	u32 *skip_key_load;

	init_sh_desc(desc, HDR_SHARE_SERIAL | HDR_SAVECTX);

	/* Skip loading of key, context if already shared */
	skip_key_load = append_jump(desc, JUMP_TEST_ALL | JUMP_COND_SHRD);

	if (state == OP_ALG_AS_INIT || state == OP_ALG_AS_INITFINAL) {
		append_key_as_imm(desc, adata->key_virt, adata->keylen,
				  adata->keylen, CLASS_1 | KEY_DEST_CLASS_REG);
	} else { /* UPDATE, FINALIZE */
		if (is_xcbc_aes(adata->algtype))
			/* Load K1 */
			append_key(desc, adata->key_dma, adata->keylen,
				   CLASS_1 | KEY_DEST_CLASS_REG | KEY_ENC);
		else /* CMAC */
			append_key_as_imm(desc, adata->key_virt, adata->keylen,
					  adata->keylen, CLASS_1 |
					  KEY_DEST_CLASS_REG);
		/* Restore context */
		append_seq_load(desc, ctx_len, LDST_CLASS_1_CCB |
				LDST_SRCDST_BYTE_CONTEXT);
	}

	set_jump_tgt_here(desc, skip_key_load);

	/* Class 1 operation */
	append_operation(desc, adata->algtype | state | OP_ALG_ENCRYPT);

	/*
	 * Load from buf and/or src and write to req->result or state->context
	 * Calculate remaining bytes to read
	 */
	append_math_add(desc, VARSEQINLEN, SEQINLEN, REG0, CAAM_CMD_SZ);

	/* Read remaining bytes */
	append_seq_fifo_load(desc, 0, FIFOLD_CLASS_CLASS1 | FIFOLD_TYPE_LAST1 |
			     FIFOLD_TYPE_MSG | FIFOLDST_VLF);

	/*
	 * Save context:
	 * - xcbc: partial hash, keys K2 and K3
	 * - cmac: partial hash, constant L = E(K,0)
	 */
	append_seq_store(desc, digestsize, LDST_CLASS_1_CCB |
			 LDST_SRCDST_BYTE_CONTEXT);
	if (is_xcbc_aes(adata->algtype) && state == OP_ALG_AS_INIT)
		/* Save K1 */
		append_fifo_store(desc, adata->key_dma, adata->keylen,
				  LDST_CLASS_1_CCB | FIFOST_TYPE_KEY_KEK);
}