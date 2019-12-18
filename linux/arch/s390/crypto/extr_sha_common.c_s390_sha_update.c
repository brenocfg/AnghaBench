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
struct shash_desc {int /*<<< orphan*/  tfm; } ;
struct s390_sha_ctx {unsigned int count; int /*<<< orphan*/  const* buf; int /*<<< orphan*/  state; int /*<<< orphan*/  func; } ;

/* Variables and functions */
 int /*<<< orphan*/  cpacf_kimd (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/  const*,unsigned int) ; 
 unsigned int crypto_shash_blocksize (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,unsigned int) ; 
 struct s390_sha_ctx* shash_desc_ctx (struct shash_desc*) ; 

int s390_sha_update(struct shash_desc *desc, const u8 *data, unsigned int len)
{
	struct s390_sha_ctx *ctx = shash_desc_ctx(desc);
	unsigned int bsize = crypto_shash_blocksize(desc->tfm);
	unsigned int index, n;

	/* how much is already in the buffer? */
	index = ctx->count % bsize;
	ctx->count += len;

	if ((index + len) < bsize)
		goto store;

	/* process one stored block */
	if (index) {
		memcpy(ctx->buf + index, data, bsize - index);
		cpacf_kimd(ctx->func, ctx->state, ctx->buf, bsize);
		data += bsize - index;
		len -= bsize - index;
		index = 0;
	}

	/* process as many blocks as possible */
	if (len >= bsize) {
		n = (len / bsize) * bsize;
		cpacf_kimd(ctx->func, ctx->state, data, n);
		data += n;
		len -= n;
	}
store:
	if (len)
		memcpy(ctx->buf + index , data, len);

	return 0;
}