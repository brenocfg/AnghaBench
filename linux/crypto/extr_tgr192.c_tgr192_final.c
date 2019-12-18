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
typedef  int u32 ;
struct tgr192_ctx {int nblocks; int count; int* hash; int /*<<< orphan*/  c; int /*<<< orphan*/  b; int /*<<< orphan*/  a; } ;
struct shash_desc {int dummy; } ;
typedef  int /*<<< orphan*/  __le32 ;
typedef  int /*<<< orphan*/  __be64 ;

/* Variables and functions */
 int /*<<< orphan*/  cpu_to_be64 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpu_to_le32 (int) ; 
 int /*<<< orphan*/  memset (int*,int /*<<< orphan*/ ,int) ; 
 struct tgr192_ctx* shash_desc_ctx (struct shash_desc*) ; 
 int /*<<< orphan*/  tgr192_transform (struct tgr192_ctx*,int*) ; 
 int /*<<< orphan*/  tgr192_update (struct shash_desc*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int tgr192_final(struct shash_desc *desc, u8 * out)
{
	struct tgr192_ctx *tctx = shash_desc_ctx(desc);
	__be64 *dst = (__be64 *)out;
	__be64 *be64p;
	__le32 *le32p;
	u32 t, msb, lsb;

	tgr192_update(desc, NULL, 0); /* flush */ ;

	msb = 0;
	t = tctx->nblocks;
	if ((lsb = t << 6) < t) { /* multiply by 64 to make a byte count */
		msb++;
	}
	msb += t >> 26;
	t = lsb;
	if ((lsb = t + tctx->count) < t) {	/* add the count */
		msb++;
	}
	t = lsb;
	if ((lsb = t << 3) < t)	{ /* multiply by 8 to make a bit count */
		msb++;
	}
	msb += t >> 29;

	if (tctx->count < 56) {	/* enough room */
		tctx->hash[tctx->count++] = 0x01;	/* pad */
		while (tctx->count < 56) {
			tctx->hash[tctx->count++] = 0;	/* pad */
		}
	} else {		/* need one extra block */
		tctx->hash[tctx->count++] = 0x01;	/* pad character */
		while (tctx->count < 64) {
			tctx->hash[tctx->count++] = 0;
		}
		tgr192_update(desc, NULL, 0); /* flush */ ;
		memset(tctx->hash, 0, 56);    /* fill next block with zeroes */
	}
	/* append the 64 bit count */
	le32p = (__le32 *)&tctx->hash[56];
	le32p[0] = cpu_to_le32(lsb);
	le32p[1] = cpu_to_le32(msb);

	tgr192_transform(tctx, tctx->hash);

	be64p = (__be64 *)tctx->hash;
	dst[0] = be64p[0] = cpu_to_be64(tctx->a);
	dst[1] = be64p[1] = cpu_to_be64(tctx->b);
	dst[2] = be64p[2] = cpu_to_be64(tctx->c);

	return 0;
}