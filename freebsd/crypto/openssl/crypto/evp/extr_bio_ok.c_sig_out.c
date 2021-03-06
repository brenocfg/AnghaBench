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
struct TYPE_3__ {int buf_len; int blockout; scalar_t__ sigio; int /*<<< orphan*/ * buf; int /*<<< orphan*/ * md; } ;
typedef  int /*<<< orphan*/  EVP_MD_CTX ;
typedef  int /*<<< orphan*/  EVP_MD ;
typedef  TYPE_1__ BIO_OK_CTX ;
typedef  int /*<<< orphan*/  BIO ;

/* Variables and functions */
 int /*<<< orphan*/  BIO_clear_retry_flags (int /*<<< orphan*/ *) ; 
 TYPE_1__* BIO_get_data (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  EVP_DigestFinal_ex (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  EVP_DigestInit_ex (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  EVP_DigestUpdate (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * EVP_MD_CTX_md (int /*<<< orphan*/ *) ; 
 void* EVP_MD_CTX_md_data (int /*<<< orphan*/ *) ; 
 int EVP_MD_size (int /*<<< orphan*/  const*) ; 
 int OK_BLOCK_SIZE ; 
 scalar_t__ RAND_bytes (void*,int) ; 
 int /*<<< orphan*/  WELLKNOWN ; 
 int /*<<< orphan*/  longswap (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,void*,int) ; 
 int /*<<< orphan*/  strlen (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int sig_out(BIO *b)
{
    BIO_OK_CTX *ctx;
    EVP_MD_CTX *md;
    const EVP_MD *digest;
    int md_size;
    void *md_data;

    ctx = BIO_get_data(b);
    md = ctx->md;
    digest = EVP_MD_CTX_md(md);
    md_size = EVP_MD_size(digest);
    md_data = EVP_MD_CTX_md_data(md);

    if (ctx->buf_len + 2 * md_size > OK_BLOCK_SIZE)
        return 1;

    if (!EVP_DigestInit_ex(md, digest, NULL))
        goto berr;
    /*
     * FIXME: there's absolutely no guarantee this makes any sense at all,
     * particularly now EVP_MD_CTX has been restructured.
     */
    if (RAND_bytes(md_data, md_size) <= 0)
        goto berr;
    memcpy(&(ctx->buf[ctx->buf_len]), md_data, md_size);
    longswap(&(ctx->buf[ctx->buf_len]), md_size);
    ctx->buf_len += md_size;

    if (!EVP_DigestUpdate(md, WELLKNOWN, strlen(WELLKNOWN)))
        goto berr;
    if (!EVP_DigestFinal_ex(md, &(ctx->buf[ctx->buf_len]), NULL))
        goto berr;
    ctx->buf_len += md_size;
    ctx->blockout = 1;
    ctx->sigio = 0;
    return 1;
 berr:
    BIO_clear_retry_flags(b);
    return 0;
}