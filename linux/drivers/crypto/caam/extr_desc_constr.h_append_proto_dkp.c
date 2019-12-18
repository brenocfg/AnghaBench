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
struct alginfo {int algtype; int keylen; int keylen_pad; int /*<<< orphan*/  key_dma; int /*<<< orphan*/  key_virt; scalar_t__ key_inline; } ;

/* Variables and functions */
 int ALIGN (int,int) ; 
 int CAAM_CMD_SZ ; 
 int CAAM_PTR_SZ ; 
 int OP_ALG_ALGSEL_SHIFT ; 
 int OP_ALG_ALGSEL_SUBMASK ; 
 int OP_PCL_DKP_DST_IMM ; 
 int OP_PCL_DKP_DST_PTR ; 
 int OP_PCL_DKP_SRC_IMM ; 
 int OP_PCL_DKP_SRC_PTR ; 
 int OP_TYPE_UNI_PROTOCOL ; 
 int /*<<< orphan*/  append_data (int* const,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  append_operation (int* const,int) ; 
 int /*<<< orphan*/  append_ptr (int* const,int /*<<< orphan*/ ) ; 
 scalar_t__ caam32_to_cpu (int) ; 
 int cpu_to_caam32 (scalar_t__) ; 

__attribute__((used)) static inline void append_proto_dkp(u32 * const desc, struct alginfo *adata)
{
	u32 protid;

	/*
	 * Quick & dirty translation from OP_ALG_ALGSEL_{MD5, SHA*}
	 * to OP_PCLID_DKP_{MD5, SHA*}
	 */
	protid = (adata->algtype & OP_ALG_ALGSEL_SUBMASK) |
		 (0x20 << OP_ALG_ALGSEL_SHIFT);

	if (adata->key_inline) {
		int words;

		if (adata->keylen > adata->keylen_pad) {
			append_operation(desc, OP_TYPE_UNI_PROTOCOL | protid |
					 OP_PCL_DKP_SRC_PTR |
					 OP_PCL_DKP_DST_IMM | adata->keylen);
			append_ptr(desc, adata->key_dma);

			words = (ALIGN(adata->keylen_pad, CAAM_CMD_SZ) -
				 CAAM_PTR_SZ) / CAAM_CMD_SZ;
		} else {
			append_operation(desc, OP_TYPE_UNI_PROTOCOL | protid |
					 OP_PCL_DKP_SRC_IMM |
					 OP_PCL_DKP_DST_IMM | adata->keylen);
			append_data(desc, adata->key_virt, adata->keylen);

			words = (ALIGN(adata->keylen_pad, CAAM_CMD_SZ) -
				 ALIGN(adata->keylen, CAAM_CMD_SZ)) /
				CAAM_CMD_SZ;
		}

		/* Reserve space in descriptor buffer for the derived key */
		if (words)
			(*desc) = cpu_to_caam32(caam32_to_cpu(*desc) + words);
	} else {
		append_operation(desc, OP_TYPE_UNI_PROTOCOL | protid |
				 OP_PCL_DKP_SRC_PTR | OP_PCL_DKP_DST_PTR |
				 adata->keylen);
		append_ptr(desc, adata->key_dma);
	}
}