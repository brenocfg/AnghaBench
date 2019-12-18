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
struct alginfo {int algtype; scalar_t__ keylen; int /*<<< orphan*/  keylen_pad; int /*<<< orphan*/  key_virt; } ;

/* Variables and functions */
 int /*<<< orphan*/  CAAM_CMD_SZ ; 
 int CLASS_2 ; 
 int FIFOLD_CLASS_CLASS2 ; 
 int FIFOLD_TYPE_LAST2 ; 
 int FIFOLD_TYPE_MSG ; 
 int /*<<< orphan*/  HDR_SHARE_SERIAL ; 
 int JUMP_COND_SHRD ; 
 int JUMP_JSL ; 
 int JUMP_TEST_ALL ; 
 int KEY_DEST_MDHA_SPLIT ; 
 int KEY_ENC ; 
 int KEY_VLF ; 
 int LDST_CLASS_2_CCB ; 
 int LDST_SRCDST_BYTE_CONTEXT ; 
 int OP_ALG_AAI_HMAC_PRECOMP ; 
 int OP_ALG_AS_UPDATE ; 
 int OP_ALG_ENCRYPT ; 
 int /*<<< orphan*/  REG0 ; 
 int /*<<< orphan*/  SEQINLEN ; 
 int /*<<< orphan*/  VARSEQINLEN ; 
 int* append_jump (int* const,int) ; 
 int /*<<< orphan*/  append_key_as_imm (int* const,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int) ; 
 int /*<<< orphan*/  append_math_add (int* const,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  append_operation (int* const,int) ; 
 int /*<<< orphan*/  append_proto_dkp (int* const,struct alginfo*) ; 
 int /*<<< orphan*/  append_seq_fifo_load (int* const,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  append_seq_load (int* const,int,int) ; 
 int /*<<< orphan*/  append_seq_store (int* const,int,int) ; 
 int /*<<< orphan*/  init_sh_desc (int* const,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_jump_tgt_here (int* const,int*) ; 

void cnstr_shdsc_ahash(u32 * const desc, struct alginfo *adata, u32 state,
		       int digestsize, int ctx_len, bool import_ctx, int era)
{
	u32 op = adata->algtype;

	init_sh_desc(desc, HDR_SHARE_SERIAL);

	/* Append key if it has been set; ahash update excluded */
	if (state != OP_ALG_AS_UPDATE && adata->keylen) {
		u32 *skip_key_load;

		/* Skip key loading if already shared */
		skip_key_load = append_jump(desc, JUMP_JSL | JUMP_TEST_ALL |
					    JUMP_COND_SHRD);

		if (era < 6)
			append_key_as_imm(desc, adata->key_virt,
					  adata->keylen_pad,
					  adata->keylen, CLASS_2 |
					  KEY_DEST_MDHA_SPLIT | KEY_ENC);
		else
			append_proto_dkp(desc, adata);

		set_jump_tgt_here(desc, skip_key_load);

		op |= OP_ALG_AAI_HMAC_PRECOMP;
	}

	/* If needed, import context from software */
	if (import_ctx)
		append_seq_load(desc, ctx_len, LDST_CLASS_2_CCB |
				LDST_SRCDST_BYTE_CONTEXT);

	/* Class 2 operation */
	append_operation(desc, op | state | OP_ALG_ENCRYPT);

	/*
	 * Load from buf and/or src and write to req->result or state->context
	 * Calculate remaining bytes to read
	 */
	append_math_add(desc, VARSEQINLEN, SEQINLEN, REG0, CAAM_CMD_SZ);
	/* Read remaining bytes */
	append_seq_fifo_load(desc, 0, FIFOLD_CLASS_CLASS2 | FIFOLD_TYPE_LAST2 |
			     FIFOLD_TYPE_MSG | KEY_VLF);
	/* Store class2 context bytes */
	append_seq_store(desc, digestsize, LDST_CLASS_2_CCB |
			 LDST_SRCDST_BYTE_CONTEXT);
}