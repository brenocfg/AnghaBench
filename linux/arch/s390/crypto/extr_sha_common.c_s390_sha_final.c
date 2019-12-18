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
typedef  int /*<<< orphan*/  u8 ;
typedef  int u64 ;
typedef  int /*<<< orphan*/  u32 ;
struct shash_desc {int /*<<< orphan*/  tfm; } ;
struct s390_sha_ctx {unsigned int count; int func; int* state; int /*<<< orphan*/  buf; } ;
typedef  int /*<<< orphan*/  bits ;

/* Variables and functions */
#define  CPACF_KLMD_SHA3_224 134 
#define  CPACF_KLMD_SHA3_256 133 
#define  CPACF_KLMD_SHA3_384 132 
#define  CPACF_KLMD_SHA3_512 131 
#define  CPACF_KLMD_SHA_1 130 
#define  CPACF_KLMD_SHA_256 129 
#define  CPACF_KLMD_SHA_512 128 
 int EINVAL ; 
 int /*<<< orphan*/  cpacf_klmd (int,int*,int /*<<< orphan*/ ,unsigned int) ; 
 unsigned int crypto_shash_blocksize (int /*<<< orphan*/ ) ; 
 int crypto_shash_digestsize (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int*,int) ; 
 int /*<<< orphan*/  memset (struct s390_sha_ctx*,int,int) ; 
 int s390_crypto_shash_parmsize (int) ; 
 struct s390_sha_ctx* shash_desc_ctx (struct shash_desc*) ; 

int s390_sha_final(struct shash_desc *desc, u8 *out)
{
	struct s390_sha_ctx *ctx = shash_desc_ctx(desc);
	unsigned int bsize = crypto_shash_blocksize(desc->tfm);
	u64 bits;
	unsigned int n, mbl_offset;

	n = ctx->count % bsize;
	bits = ctx->count * 8;
	mbl_offset = s390_crypto_shash_parmsize(ctx->func) / sizeof(u32);
	if (mbl_offset < 0)
		return -EINVAL;

	/* set total msg bit length (mbl) in CPACF parmblock */
	switch (ctx->func) {
	case CPACF_KLMD_SHA_1:
	case CPACF_KLMD_SHA_256:
		memcpy(ctx->state + mbl_offset, &bits, sizeof(bits));
		break;
	case CPACF_KLMD_SHA_512:
		/*
		 * the SHA512 parmblock has a 128-bit mbl field, clear
		 * high-order u64 field, copy bits to low-order u64 field
		 */
		memset(ctx->state + mbl_offset, 0x00, sizeof(bits));
		mbl_offset += sizeof(u64) / sizeof(u32);
		memcpy(ctx->state + mbl_offset, &bits, sizeof(bits));
		break;
	case CPACF_KLMD_SHA3_224:
	case CPACF_KLMD_SHA3_256:
	case CPACF_KLMD_SHA3_384:
	case CPACF_KLMD_SHA3_512:
		break;
	default:
		return -EINVAL;
	}

	cpacf_klmd(ctx->func, ctx->state, ctx->buf, n);

	/* copy digest to out */
	memcpy(out, ctx->state, crypto_shash_digestsize(desc->tfm));
	/* wipe context */
	memset(ctx, 0, sizeof *ctx);

	return 0;
}