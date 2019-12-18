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
struct TYPE_2__ {int /*<<< orphan*/  mac_iv; int /*<<< orphan*/  mac_digest; int /*<<< orphan*/  mac_src_p; int /*<<< orphan*/  enc_iv; int /*<<< orphan*/  enc_key_p; int /*<<< orphan*/  enc_p; } ;
struct mv_cesa_op_ctx {TYPE_1__ desc; } ;
struct mv_cesa_engine {int sram_dma; } ;

/* Variables and functions */
 int /*<<< orphan*/  CESA_SA_DESC_CRYPT_DATA (int) ; 
 int /*<<< orphan*/  CESA_SA_DESC_CRYPT_IV (int) ; 
 int /*<<< orphan*/  CESA_SA_DESC_CRYPT_KEY (int) ; 
 int /*<<< orphan*/  CESA_SA_DESC_MAC_DATA (int) ; 
 int /*<<< orphan*/  CESA_SA_DESC_MAC_DATA_MSK ; 
 int /*<<< orphan*/  CESA_SA_DESC_MAC_DIGEST (int) ; 
 int /*<<< orphan*/  CESA_SA_DESC_MAC_DIGEST_MSK ; 
 int /*<<< orphan*/  CESA_SA_DESC_MAC_IV (int) ; 
 int CESA_SA_SRAM_MSK ; 

__attribute__((used)) static inline void mv_cesa_adjust_op(struct mv_cesa_engine *engine,
				     struct mv_cesa_op_ctx *op)
{
	u32 offset = engine->sram_dma & CESA_SA_SRAM_MSK;

	op->desc.enc_p = CESA_SA_DESC_CRYPT_DATA(offset);
	op->desc.enc_key_p = CESA_SA_DESC_CRYPT_KEY(offset);
	op->desc.enc_iv = CESA_SA_DESC_CRYPT_IV(offset);
	op->desc.mac_src_p &= ~CESA_SA_DESC_MAC_DATA_MSK;
	op->desc.mac_src_p |= CESA_SA_DESC_MAC_DATA(offset);
	op->desc.mac_digest &= ~CESA_SA_DESC_MAC_DIGEST_MSK;
	op->desc.mac_digest |= CESA_SA_DESC_MAC_DIGEST(offset);
	op->desc.mac_iv = CESA_SA_DESC_MAC_IV(offset);
}