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
typedef  int /*<<< orphan*/  u_char ;
struct umac_ctx {int /*<<< orphan*/  hash; int /*<<< orphan*/  pdf; struct umac_ctx* free_ptr; } ;
typedef  int ptrdiff_t ;
typedef  int /*<<< orphan*/  prf_key ;
typedef  int /*<<< orphan*/  aes_int_key ;

/* Variables and functions */
 int ALLOC_BOUNDARY ; 
 int /*<<< orphan*/  aes_key_setup (int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  explicit_bzero (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pdf_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uhash_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct umac_ctx* xcalloc (int,int) ; 

struct umac_ctx *umac_new(const u_char key[])
/* Dynamically allocate a umac_ctx struct, initialize variables,
 * generate subkeys from key. Align to 16-byte boundary.
 */
{
    struct umac_ctx *ctx, *octx;
    size_t bytes_to_add;
    aes_int_key prf_key;

    octx = ctx = xcalloc(1, sizeof(*ctx) + ALLOC_BOUNDARY);
    if (ctx) {
        if (ALLOC_BOUNDARY) {
            bytes_to_add = ALLOC_BOUNDARY -
                              ((ptrdiff_t)ctx & (ALLOC_BOUNDARY - 1));
            ctx = (struct umac_ctx *)((u_char *)ctx + bytes_to_add);
        }
        ctx->free_ptr = octx;
        aes_key_setup(key, prf_key);
        pdf_init(&ctx->pdf, prf_key);
        uhash_init(&ctx->hash, prf_key);
        explicit_bzero(prf_key, sizeof(prf_key));
    }

    return (ctx);
}