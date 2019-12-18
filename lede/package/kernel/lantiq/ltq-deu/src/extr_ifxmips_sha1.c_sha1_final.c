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
typedef  int u8 ;
typedef  int u64 ;
typedef  int u32 ;
struct shash_desc {int dummy; } ;
struct sha1_ctx {int count; } ;
struct deu_hash_t {int D1R; int D2R; int D3R; int D4R; int D5R; } ;

/* Variables and functions */
 int /*<<< orphan*/  CRTCL_SECT_END ; 
 int /*<<< orphan*/  CRTCL_SECT_START ; 
 scalar_t__ HASH_START ; 
 int /*<<< orphan*/  memset (struct sha1_ctx*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  sha1_update (struct shash_desc*,int const*,int) ; 
 struct sha1_ctx* shash_desc_ctx (struct shash_desc*) ; 

__attribute__((used)) static int sha1_final(struct shash_desc *desc, u8 *out)
{
    struct sha1_ctx *sctx = shash_desc_ctx(desc);
    u32 index, padlen;
    u64 t;
    u8 bits[8] = { 0, };
    static const u8 padding[64] = { 0x80, };
    volatile struct deu_hash_t *hashs = (struct deu_hash_t *) HASH_START;
    unsigned long flag;

    t = sctx->count;
    bits[7] = 0xff & t;
    t >>= 8;
    bits[6] = 0xff & t;
    t >>= 8;
    bits[5] = 0xff & t;
    t >>= 8;
    bits[4] = 0xff & t;
    t >>= 8;
    bits[3] = 0xff & t;
    t >>= 8;
    bits[2] = 0xff & t;
    t >>= 8;
    bits[1] = 0xff & t;
    t >>= 8;
    bits[0] = 0xff & t;

    /* Pad out to 56 mod 64 */
    index = (sctx->count >> 3) & 0x3f;
    padlen = (index < 56) ? (56 - index) : ((64 + 56) - index);
    sha1_update (desc, padding, padlen);

    /* Append length */
    sha1_update (desc, bits, sizeof bits);

    CRTCL_SECT_START;

    *((u32 *) out + 0) = hashs->D1R;
    *((u32 *) out + 1) = hashs->D2R;
    *((u32 *) out + 2) = hashs->D3R;
    *((u32 *) out + 3) = hashs->D4R;
    *((u32 *) out + 4) = hashs->D5R;

    CRTCL_SECT_END;

    // Wipe context
    memset (sctx, 0, sizeof *sctx);

    return 0;
}