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
typedef  char u8 ;
typedef  int /*<<< orphan*/  u64 ;
struct shash_desc {int dummy; } ;
struct md5_state {int byte_count; int /*<<< orphan*/ * hash; scalar_t__ block; } ;
typedef  int /*<<< orphan*/  __le64 ;
typedef  int /*<<< orphan*/  __le32 ;

/* Variables and functions */
 int /*<<< orphan*/  cpu_to_le32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpu_to_le64 (int) ; 
 int /*<<< orphan*/  memset (char*,int,int) ; 
 int /*<<< orphan*/  ppc_md5_clear_context (struct md5_state*) ; 
 int /*<<< orphan*/  ppc_md5_transform (int /*<<< orphan*/ *,char const*,int) ; 
 struct md5_state* shash_desc_ctx (struct shash_desc*) ; 

__attribute__((used)) static int ppc_md5_final(struct shash_desc *desc, u8 *out)
{
	struct md5_state *sctx = shash_desc_ctx(desc);
	const unsigned int offset = sctx->byte_count & 0x3f;
	const u8 *src = (const u8 *)sctx->block;
	u8 *p = (u8 *)src + offset;
	int padlen = 55 - offset;
	__le64 *pbits = (__le64 *)((char *)sctx->block + 56);
	__le32 *dst = (__le32 *)out;

	*p++ = 0x80;

	if (padlen < 0) {
		memset(p, 0x00, padlen + sizeof (u64));
		ppc_md5_transform(sctx->hash, src, 1);
		p = (char *)sctx->block;
		padlen = 56;
	}

	memset(p, 0, padlen);
	*pbits = cpu_to_le64(sctx->byte_count << 3);
	ppc_md5_transform(sctx->hash, src, 1);

	dst[0] = cpu_to_le32(sctx->hash[0]);
	dst[1] = cpu_to_le32(sctx->hash[1]);
	dst[2] = cpu_to_le32(sctx->hash[2]);
	dst[3] = cpu_to_le32(sctx->hash[3]);

	ppc_md5_clear_context(sctx);
	return 0;
}