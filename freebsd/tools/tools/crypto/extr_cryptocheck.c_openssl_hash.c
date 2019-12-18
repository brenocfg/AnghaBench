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
struct alg {int /*<<< orphan*/  name; } ;
typedef  int /*<<< orphan*/  EVP_MD_CTX ;
typedef  int /*<<< orphan*/  EVP_MD ;

/* Variables and functions */
 int /*<<< orphan*/  ERR_error_string (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ERR_get_error () ; 
 int EVP_DigestFinal_ex (int /*<<< orphan*/ *,void*,unsigned int*) ; 
 int EVP_DigestInit_ex (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/ *) ; 
 int EVP_DigestUpdate (int /*<<< orphan*/ *,void const*,size_t) ; 
 int /*<<< orphan*/ * EVP_MD_CTX_create () ; 
 int /*<<< orphan*/  EVP_MD_CTX_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  errx (int,char*,int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
openssl_hash(struct alg *alg, const EVP_MD *md, const void *buffer,
    size_t size, void *digest_out, unsigned *digest_sz_out)
{
	EVP_MD_CTX *mdctx;
	const char *errs;
	int rc;

	errs = "";

	mdctx = EVP_MD_CTX_create();
	if (mdctx == NULL)
		goto err_out;

	rc = EVP_DigestInit_ex(mdctx, md, NULL);
	if (rc != 1)
		goto err_out;

	rc = EVP_DigestUpdate(mdctx, buffer, size);
	if (rc != 1)
		goto err_out;

	rc = EVP_DigestFinal_ex(mdctx, digest_out, digest_sz_out);
	if (rc != 1)
		goto err_out;

	EVP_MD_CTX_destroy(mdctx);
	return;

err_out:
	errx(1, "OpenSSL %s HASH failed%s: %s", alg->name, errs,
	    ERR_error_string(ERR_get_error(), NULL));
}