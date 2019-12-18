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
typedef  int /*<<< orphan*/  u8 ;
typedef  scalar_t__ u16 ;
struct nx842_crypto_param {unsigned int iremain; unsigned int oremain; unsigned int ototal; int /*<<< orphan*/ * out; int /*<<< orphan*/ * in; } ;
struct nx842_crypto_header_group {int /*<<< orphan*/  uncompressed_length; int /*<<< orphan*/  compressed_length; int /*<<< orphan*/  padding; } ;
struct nx842_crypto_header {int groups; struct nx842_crypto_header_group* group; int /*<<< orphan*/  ignore; int /*<<< orphan*/  magic; } ;
struct nx842_crypto_ctx {int /*<<< orphan*/  lock; struct nx842_crypto_header header; TYPE_1__* driver; } ;
struct nx842_constraints {int dummy; } ;
struct crypto_tfm {int dummy; } ;
struct TYPE_2__ {struct nx842_constraints* constraints; } ;

/* Variables and functions */
 int EINVAL ; 
 int EOVERFLOW ; 
 int NX842_CRYPTO_GROUP_MAX ; 
 int NX842_CRYPTO_HEADER_SIZE (int) ; 
 scalar_t__ NX842_CRYPTO_MAGIC ; 
 scalar_t__ be16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  check_constraints (struct nx842_constraints*) ; 
 int /*<<< orphan*/  cpu_to_be32 (unsigned int) ; 
 struct nx842_crypto_ctx* crypto_tfm_ctx (struct crypto_tfm*) ; 
 int decompress (struct nx842_crypto_ctx*,struct nx842_crypto_param*,struct nx842_crypto_header_group*,struct nx842_constraints*,scalar_t__) ; 
 int /*<<< orphan*/  memcpy (struct nx842_crypto_header*,int /*<<< orphan*/  const*,int) ; 
 int /*<<< orphan*/  pr_debug (char*,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  pr_err (char*,...) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

int nx842_crypto_decompress(struct crypto_tfm *tfm,
			    const u8 *src, unsigned int slen,
			    u8 *dst, unsigned int *dlen)
{
	struct nx842_crypto_ctx *ctx = crypto_tfm_ctx(tfm);
	struct nx842_crypto_header *hdr;
	struct nx842_crypto_param p;
	struct nx842_constraints c = *ctx->driver->constraints;
	int n, ret, hdr_len;
	u16 ignore = 0;

	check_constraints(&c);

	p.in = (u8 *)src;
	p.iremain = slen;
	p.out = dst;
	p.oremain = *dlen;
	p.ototal = 0;

	*dlen = 0;

	hdr = (struct nx842_crypto_header *)src;

	spin_lock_bh(&ctx->lock);

	/* If it doesn't start with our header magic number, assume it's a raw
	 * 842 compressed buffer and pass it directly to the hardware driver
	 */
	if (be16_to_cpu(hdr->magic) != NX842_CRYPTO_MAGIC) {
		struct nx842_crypto_header_group g = {
			.padding =		0,
			.compressed_length =	cpu_to_be32(p.iremain),
			.uncompressed_length =	cpu_to_be32(p.oremain),
		};

		ret = decompress(ctx, &p, &g, &c, 0);
		if (ret)
			goto unlock;

		goto success;
	}

	if (!hdr->groups) {
		pr_err("header has no groups\n");
		ret = -EINVAL;
		goto unlock;
	}
	if (hdr->groups > NX842_CRYPTO_GROUP_MAX) {
		pr_err("header has too many groups %x, max %x\n",
		       hdr->groups, NX842_CRYPTO_GROUP_MAX);
		ret = -EINVAL;
		goto unlock;
	}

	hdr_len = NX842_CRYPTO_HEADER_SIZE(hdr->groups);
	if (hdr_len > slen) {
		ret = -EOVERFLOW;
		goto unlock;
	}

	memcpy(&ctx->header, src, hdr_len);
	hdr = &ctx->header;

	for (n = 0; n < hdr->groups; n++) {
		/* ignore applies to last group */
		if (n + 1 == hdr->groups)
			ignore = be16_to_cpu(hdr->ignore);

		ret = decompress(ctx, &p, &hdr->group[n], &c, ignore);
		if (ret)
			goto unlock;
	}

success:
	*dlen = p.ototal;

	pr_debug("decompress total slen %x dlen %x\n", slen, *dlen);

	ret = 0;

unlock:
	spin_unlock_bh(&ctx->lock);

	return ret;
}