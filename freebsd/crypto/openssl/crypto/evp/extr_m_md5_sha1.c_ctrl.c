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
struct md5_sha1_ctx {int /*<<< orphan*/  sha1; int /*<<< orphan*/  md5; } ;
typedef  int /*<<< orphan*/  sha1tmp ;
typedef  int /*<<< orphan*/  padtmp ;
typedef  int /*<<< orphan*/  md5tmp ;
typedef  int /*<<< orphan*/  EVP_MD_CTX ;

/* Variables and functions */
 int EVP_CTRL_SSL3_MASTER_SECRET ; 
 struct md5_sha1_ctx* EVP_MD_CTX_md_data (int /*<<< orphan*/ *) ; 
 int MD5_DIGEST_LENGTH ; 
 int /*<<< orphan*/  MD5_Final (unsigned char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  MD5_Update (int /*<<< orphan*/ *,unsigned char*,int) ; 
 int /*<<< orphan*/  OPENSSL_cleanse (unsigned char*,int) ; 
 int /*<<< orphan*/  SHA1_Final (unsigned char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SHA1_Update (int /*<<< orphan*/ *,unsigned char*,int) ; 
 int SHA_DIGEST_LENGTH ; 
 int /*<<< orphan*/  init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (unsigned char*,int,int) ; 
 scalar_t__ update (int /*<<< orphan*/ *,void*,int) ; 

__attribute__((used)) static int ctrl(EVP_MD_CTX *ctx, int cmd, int mslen, void *ms)
{
    unsigned char padtmp[48];
    unsigned char md5tmp[MD5_DIGEST_LENGTH];
    unsigned char sha1tmp[SHA_DIGEST_LENGTH];
    struct md5_sha1_ctx *mctx;

    if (cmd != EVP_CTRL_SSL3_MASTER_SECRET)
        return -2;

    if (ctx == NULL)
        return 0;

    mctx = EVP_MD_CTX_md_data(ctx);

    /* SSLv3 client auth handling: see RFC-6101 5.6.8 */
    if (mslen != 48)
        return 0;

    /* At this point hash contains all handshake messages, update
     * with master secret and pad_1.
     */

    if (update(ctx, ms, mslen) <= 0)
        return 0;

    /* Set padtmp to pad_1 value */
    memset(padtmp, 0x36, sizeof(padtmp));

    if (!MD5_Update(&mctx->md5, padtmp, sizeof(padtmp)))
        return 0;

    if (!MD5_Final(md5tmp, &mctx->md5))
        return 0;

    if (!SHA1_Update(&mctx->sha1, padtmp, 40))
        return 0;

    if (!SHA1_Final(sha1tmp, &mctx->sha1))
        return 0;

    /* Reinitialise context */

    if (!init(ctx))
        return 0;

    if (update(ctx, ms, mslen) <= 0)
        return 0;

    /* Set padtmp to pad_2 value */
    memset(padtmp, 0x5c, sizeof(padtmp));

    if (!MD5_Update(&mctx->md5, padtmp, sizeof(padtmp)))
        return 0;

    if (!MD5_Update(&mctx->md5, md5tmp, sizeof(md5tmp)))
        return 0;

    if (!SHA1_Update(&mctx->sha1, padtmp, 40))
        return 0;

    if (!SHA1_Update(&mctx->sha1, sha1tmp, sizeof(sha1tmp)))
        return 0;

    /* Now when ctx is finalised it will return the SSL v3 hash value */

    OPENSSL_cleanse(md5tmp, sizeof(md5tmp));
    OPENSSL_cleanse(sha1tmp, sizeof(sha1tmp));

    return 1;

}