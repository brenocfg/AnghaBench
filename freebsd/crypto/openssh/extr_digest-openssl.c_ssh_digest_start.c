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
struct ssh_digest_ctx {int alg; int /*<<< orphan*/ * mdctx; } ;
struct ssh_digest {int /*<<< orphan*/  (* mdfunc ) () ;} ;

/* Variables and functions */
 int EVP_DigestInit_ex (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * EVP_MD_CTX_new () ; 
 struct ssh_digest_ctx* calloc (int,int) ; 
 int /*<<< orphan*/  free (struct ssh_digest_ctx*) ; 
 struct ssh_digest* ssh_digest_by_alg (int) ; 
 int /*<<< orphan*/  ssh_digest_free (struct ssh_digest_ctx*) ; 
 int /*<<< orphan*/  stub1 () ; 

struct ssh_digest_ctx *
ssh_digest_start(int alg)
{
	const struct ssh_digest *digest = ssh_digest_by_alg(alg);
	struct ssh_digest_ctx *ret;

	if (digest == NULL || ((ret = calloc(1, sizeof(*ret))) == NULL))
		return NULL;
	ret->alg = alg;
	if ((ret->mdctx = EVP_MD_CTX_new()) == NULL) {
		free(ret);
		return NULL;
	}
	if (EVP_DigestInit_ex(ret->mdctx, digest->mdfunc(), NULL) != 1) {
		ssh_digest_free(ret);
		return NULL;
	}
	return ret;
}