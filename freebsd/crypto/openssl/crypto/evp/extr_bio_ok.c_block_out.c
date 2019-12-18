#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {size_t buf_len; unsigned char* buf; int blockout; int /*<<< orphan*/ * md; } ;
typedef  int /*<<< orphan*/  EVP_MD_CTX ;
typedef  int /*<<< orphan*/  EVP_MD ;
typedef  TYPE_1__ BIO_OK_CTX ;
typedef  int /*<<< orphan*/  BIO ;

/* Variables and functions */
 int /*<<< orphan*/  BIO_clear_retry_flags (int /*<<< orphan*/ *) ; 
 TYPE_1__* BIO_get_data (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  EVP_DigestFinal_ex (int /*<<< orphan*/ *,unsigned char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  EVP_DigestUpdate (int /*<<< orphan*/ *,unsigned char*,unsigned long) ; 
 int /*<<< orphan*/ * EVP_MD_CTX_md (int /*<<< orphan*/ *) ; 
 int EVP_MD_size (int /*<<< orphan*/  const*) ; 
 size_t OK_BLOCK_BLOCK ; 

__attribute__((used)) static int block_out(BIO *b)
{
    BIO_OK_CTX *ctx;
    EVP_MD_CTX *md;
    unsigned long tl;
    const EVP_MD *digest;
    int md_size;

    ctx = BIO_get_data(b);
    md = ctx->md;
    digest = EVP_MD_CTX_md(md);
    md_size = EVP_MD_size(digest);

    tl = ctx->buf_len - OK_BLOCK_BLOCK;
    ctx->buf[0] = (unsigned char)(tl >> 24);
    ctx->buf[1] = (unsigned char)(tl >> 16);
    ctx->buf[2] = (unsigned char)(tl >> 8);
    ctx->buf[3] = (unsigned char)(tl);
    if (!EVP_DigestUpdate(md,
                          (unsigned char *)&(ctx->buf[OK_BLOCK_BLOCK]), tl))
        goto berr;
    if (!EVP_DigestFinal_ex(md, &(ctx->buf[ctx->buf_len]), NULL))
        goto berr;
    ctx->buf_len += md_size;
    ctx->blockout = 1;
    return 1;
 berr:
    BIO_clear_retry_flags(b);
    return 0;
}