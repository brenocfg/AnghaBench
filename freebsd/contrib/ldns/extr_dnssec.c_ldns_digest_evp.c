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
typedef  int /*<<< orphan*/  EVP_MD_CTX ;
typedef  int /*<<< orphan*/  EVP_MD ;

/* Variables and functions */
 int /*<<< orphan*/  EVP_DigestFinal_ex (int /*<<< orphan*/ *,unsigned char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  EVP_DigestInit_ex (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  EVP_DigestUpdate (int /*<<< orphan*/ *,unsigned char const*,unsigned int) ; 
 int /*<<< orphan*/ * EVP_MD_CTX_create () ; 
 int /*<<< orphan*/  EVP_MD_CTX_destroy (int /*<<< orphan*/ *) ; 

int
ldns_digest_evp(const unsigned char* data, unsigned int len, unsigned char* dest,
	const EVP_MD* md)
{
	EVP_MD_CTX* ctx;
	ctx = EVP_MD_CTX_create();
	if(!ctx)
		return false;
	if(!EVP_DigestInit_ex(ctx, md, NULL) ||
		!EVP_DigestUpdate(ctx, data, len) ||
		!EVP_DigestFinal_ex(ctx, dest, NULL)) {
		EVP_MD_CTX_destroy(ctx);
		return false;
	}
	EVP_MD_CTX_destroy(ctx);
	return true;
}