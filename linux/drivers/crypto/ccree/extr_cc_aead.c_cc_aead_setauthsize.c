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
struct device {int dummy; } ;
struct crypto_aead {int dummy; } ;
struct cc_aead_ctx {unsigned int authsize; int /*<<< orphan*/  drvdata; } ;

/* Variables and functions */
 int ENOTSUPP ; 
 struct cc_aead_ctx* crypto_aead_ctx (struct crypto_aead*) ; 
 unsigned int crypto_aead_maxauthsize (struct crypto_aead*) ; 
 int /*<<< orphan*/  dev_dbg (struct device*,char*,unsigned int) ; 
 struct device* drvdata_to_dev (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int cc_aead_setauthsize(struct crypto_aead *authenc,
			       unsigned int authsize)
{
	struct cc_aead_ctx *ctx = crypto_aead_ctx(authenc);
	struct device *dev = drvdata_to_dev(ctx->drvdata);

	/* Unsupported auth. sizes */
	if (authsize == 0 ||
	    authsize > crypto_aead_maxauthsize(authenc)) {
		return -ENOTSUPP;
	}

	ctx->authsize = authsize;
	dev_dbg(dev, "authlen=%d\n", ctx->authsize);

	return 0;
}