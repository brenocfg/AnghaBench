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
struct TYPE_3__ {int /*<<< orphan*/  digest; } ;
typedef  int /*<<< orphan*/  EVP_PKEY_CTX ;
typedef  int /*<<< orphan*/  EVP_PKEY ;
typedef  TYPE_1__ EVP_MD_CTX ;
typedef  int /*<<< orphan*/  EVP_MD ;

/* Variables and functions */
 int /*<<< orphan*/  EVP_DigestInit (TYPE_1__*,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  EVP_PKEY_CTX_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * EVP_PKEY_CTX_new (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ EVP_PKEY_CTX_set_signature_md (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int EVP_PKEY_verify (int /*<<< orphan*/ *,unsigned char*,size_t,unsigned char*,size_t) ; 
 scalar_t__ EVP_PKEY_verify_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * EVP_get_digestbyname (char const*) ; 
 int /*<<< orphan*/  initialize () ; 

__attribute__((used)) static int
verify_digest (EVP_PKEY *pkey,
    const char *digest,
    unsigned char *mdata, size_t mlen,
    unsigned char *sdata, size_t slen)
{
	EVP_MD_CTX ctx;
	const EVP_MD *md = NULL;
	EVP_PKEY_CTX *pctx = NULL;
	int rc = 0;
	int i = -1;

	initialize();
	md = EVP_get_digestbyname(digest);
	EVP_DigestInit(&ctx, md);

	pctx = EVP_PKEY_CTX_new(pkey, NULL);
	if (!pctx)
		goto fail;
	if (EVP_PKEY_verify_init(pctx) <= 0)
		goto fail;
	if (EVP_PKEY_CTX_set_signature_md(pctx, ctx.digest) <= 0)
		goto fail;
	i = EVP_PKEY_verify(pctx, sdata, slen, mdata, mlen);
	if (i >= 0)
		rc = i;
fail:
	EVP_PKEY_CTX_free(pctx);
	return (rc);
}