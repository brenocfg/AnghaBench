#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct TYPE_5__ {int /*<<< orphan*/  key; } ;
struct TYPE_4__ {int /*<<< orphan*/  mode; } ;
struct TYPE_6__ {TYPE_2__ aes_ctr; TYPE_1__ hdr; } ;
struct nx_csbcpb {TYPE_3__ cpb; } ;
struct nx_crypto_ctx {int /*<<< orphan*/ * props; int /*<<< orphan*/ * ap; struct nx_csbcpb* csbcpb; } ;
struct crypto_tfm {int dummy; } ;

/* Variables and functions */
#define  AES_KEYSIZE_128 130 
#define  AES_KEYSIZE_192 129 
#define  AES_KEYSIZE_256 128 
 int EINVAL ; 
 int /*<<< orphan*/  HCOP_FC_AES ; 
 int /*<<< orphan*/  NX_CPB_SET_KEY_SIZE (struct nx_csbcpb*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NX_KS_AES_128 ; 
 int /*<<< orphan*/  NX_KS_AES_192 ; 
 int /*<<< orphan*/  NX_KS_AES_256 ; 
 int /*<<< orphan*/  NX_MODE_AES_CTR ; 
 size_t NX_PROPS_AES_128 ; 
 size_t NX_PROPS_AES_192 ; 
 size_t NX_PROPS_AES_256 ; 
 struct nx_crypto_ctx* crypto_tfm_ctx (struct crypto_tfm*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/  const*,unsigned int) ; 
 int /*<<< orphan*/  nx_ctx_init (struct nx_crypto_ctx*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ctr_aes_nx_set_key(struct crypto_tfm *tfm,
			      const u8          *in_key,
			      unsigned int       key_len)
{
	struct nx_crypto_ctx *nx_ctx = crypto_tfm_ctx(tfm);
	struct nx_csbcpb *csbcpb = nx_ctx->csbcpb;

	nx_ctx_init(nx_ctx, HCOP_FC_AES);

	switch (key_len) {
	case AES_KEYSIZE_128:
		NX_CPB_SET_KEY_SIZE(csbcpb, NX_KS_AES_128);
		nx_ctx->ap = &nx_ctx->props[NX_PROPS_AES_128];
		break;
	case AES_KEYSIZE_192:
		NX_CPB_SET_KEY_SIZE(csbcpb, NX_KS_AES_192);
		nx_ctx->ap = &nx_ctx->props[NX_PROPS_AES_192];
		break;
	case AES_KEYSIZE_256:
		NX_CPB_SET_KEY_SIZE(csbcpb, NX_KS_AES_256);
		nx_ctx->ap = &nx_ctx->props[NX_PROPS_AES_256];
		break;
	default:
		return -EINVAL;
	}

	csbcpb->cpb.hdr.mode = NX_MODE_AES_CTR;
	memcpy(csbcpb->cpb.aes_ctr.key, in_key, key_len);

	return 0;
}