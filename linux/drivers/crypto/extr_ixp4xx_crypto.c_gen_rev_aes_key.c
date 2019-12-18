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
typedef  int /*<<< orphan*/  u32 ;
struct ix_sa_dir {int /*<<< orphan*/  npe_ctx_idx; scalar_t__ npe_ctx_phys; scalar_t__ npe_ctx; } ;
struct ixp_ctx {int /*<<< orphan*/  configuring; struct ix_sa_dir decrypt; } ;
struct crypto_tfm {int dummy; } ;
struct TYPE_2__ {struct crypto_tfm* tfm; } ;
struct crypt_ctl {int /*<<< orphan*/  ctl_flags; int /*<<< orphan*/  init_len; int /*<<< orphan*/  mode; scalar_t__ icv_rev_aes; scalar_t__ crypto_ctx; scalar_t__ src_buf; int /*<<< orphan*/  crypt_len; scalar_t__ crypt_offs; TYPE_1__ data; } ;

/* Variables and functions */
 int /*<<< orphan*/  AES_BLOCK128 ; 
 int /*<<< orphan*/  BUG_ON (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CIPH_ENCR ; 
 int /*<<< orphan*/  CTL_FLAG_GEN_REVAES ; 
 int EAGAIN ; 
 int /*<<< orphan*/  NPE_OP_ENC_GEN_KEY ; 
 int /*<<< orphan*/  SEND_QID ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cpu_to_be32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  crypt_virt2phys (struct crypt_ctl*) ; 
 struct ixp_ctx* crypto_tfm_ctx (struct crypto_tfm*) ; 
 struct crypt_ctl* get_crypt_desc_emerg () ; 
 int /*<<< orphan*/  qmgr_put_entry (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qmgr_stat_overflow (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int gen_rev_aes_key(struct crypto_tfm *tfm)
{
	struct crypt_ctl *crypt;
	struct ixp_ctx *ctx = crypto_tfm_ctx(tfm);
	struct ix_sa_dir *dir = &ctx->decrypt;

	crypt = get_crypt_desc_emerg();
	if (!crypt) {
		return -EAGAIN;
	}
	*(u32*)dir->npe_ctx |= cpu_to_be32(CIPH_ENCR);

	crypt->data.tfm = tfm;
	crypt->crypt_offs = 0;
	crypt->crypt_len = AES_BLOCK128;
	crypt->src_buf = 0;
	crypt->crypto_ctx = dir->npe_ctx_phys;
	crypt->icv_rev_aes = dir->npe_ctx_phys + sizeof(u32);
	crypt->mode = NPE_OP_ENC_GEN_KEY;
	crypt->init_len = dir->npe_ctx_idx;
	crypt->ctl_flags |= CTL_FLAG_GEN_REVAES;

	atomic_inc(&ctx->configuring);
	qmgr_put_entry(SEND_QID, crypt_virt2phys(crypt));
	BUG_ON(qmgr_stat_overflow(SEND_QID));
	return 0;
}