#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct list_head {int dummy; } ;
struct TYPE_2__ {int min_keysize; int max_keysize; void* ivsize; int /*<<< orphan*/  decrypt; int /*<<< orphan*/  encrypt; int /*<<< orphan*/  setkey; } ;
struct crypto_alg {int cra_flags; int cra_ctxsize; int /*<<< orphan*/  cra_name; int /*<<< orphan*/  cra_module; int /*<<< orphan*/  cra_exit; int /*<<< orphan*/  cra_init; TYPE_1__ cra_ablkcipher; int /*<<< orphan*/ * cra_type; int /*<<< orphan*/  cra_priority; void* cra_blocksize; int /*<<< orphan*/  cra_driver_name; } ;
struct ccp_ctx {int dummy; } ;
struct ccp_crypto_ablkcipher_alg {int /*<<< orphan*/  entry; struct crypto_alg alg; } ;
struct ccp_aes_xts_def {char* name; char* drv_name; } ;

/* Variables and functions */
 void* AES_BLOCK_SIZE ; 
 int AES_MAX_KEY_SIZE ; 
 int AES_MIN_KEY_SIZE ; 
 int /*<<< orphan*/  CCP_CRA_PRIORITY ; 
 int CRYPTO_ALG_ASYNC ; 
 int CRYPTO_ALG_KERN_DRIVER_ONLY ; 
 int CRYPTO_ALG_NEED_FALLBACK ; 
 int CRYPTO_ALG_TYPE_ABLKCIPHER ; 
 int /*<<< orphan*/  CRYPTO_MAX_ALG_NAME ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  THIS_MODULE ; 
 int /*<<< orphan*/  ccp_aes_xts_cra_exit ; 
 int /*<<< orphan*/  ccp_aes_xts_cra_init ; 
 int /*<<< orphan*/  ccp_aes_xts_decrypt ; 
 int /*<<< orphan*/  ccp_aes_xts_encrypt ; 
 int /*<<< orphan*/  ccp_aes_xts_setkey ; 
 int /*<<< orphan*/  crypto_ablkcipher_type ; 
 int crypto_register_alg (struct crypto_alg*) ; 
 int /*<<< orphan*/  kfree (struct ccp_crypto_ablkcipher_alg*) ; 
 struct ccp_crypto_ablkcipher_alg* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,struct list_head*) ; 
 int /*<<< orphan*/  pr_err (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  snprintf (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,char*) ; 

__attribute__((used)) static int ccp_register_aes_xts_alg(struct list_head *head,
				    const struct ccp_aes_xts_def *def)
{
	struct ccp_crypto_ablkcipher_alg *ccp_alg;
	struct crypto_alg *alg;
	int ret;

	ccp_alg = kzalloc(sizeof(*ccp_alg), GFP_KERNEL);
	if (!ccp_alg)
		return -ENOMEM;

	INIT_LIST_HEAD(&ccp_alg->entry);

	alg = &ccp_alg->alg;

	snprintf(alg->cra_name, CRYPTO_MAX_ALG_NAME, "%s", def->name);
	snprintf(alg->cra_driver_name, CRYPTO_MAX_ALG_NAME, "%s",
		 def->drv_name);
	alg->cra_flags = CRYPTO_ALG_TYPE_ABLKCIPHER | CRYPTO_ALG_ASYNC |
			 CRYPTO_ALG_KERN_DRIVER_ONLY |
			 CRYPTO_ALG_NEED_FALLBACK;
	alg->cra_blocksize = AES_BLOCK_SIZE;
	alg->cra_ctxsize = sizeof(struct ccp_ctx);
	alg->cra_priority = CCP_CRA_PRIORITY;
	alg->cra_type = &crypto_ablkcipher_type;
	alg->cra_ablkcipher.setkey = ccp_aes_xts_setkey;
	alg->cra_ablkcipher.encrypt = ccp_aes_xts_encrypt;
	alg->cra_ablkcipher.decrypt = ccp_aes_xts_decrypt;
	alg->cra_ablkcipher.min_keysize = AES_MIN_KEY_SIZE * 2;
	alg->cra_ablkcipher.max_keysize = AES_MAX_KEY_SIZE * 2;
	alg->cra_ablkcipher.ivsize = AES_BLOCK_SIZE;
	alg->cra_init = ccp_aes_xts_cra_init;
	alg->cra_exit = ccp_aes_xts_cra_exit;
	alg->cra_module = THIS_MODULE;

	ret = crypto_register_alg(alg);
	if (ret) {
		pr_err("%s ablkcipher algorithm registration error (%d)\n",
		       alg->cra_name, ret);
		kfree(ccp_alg);
		return ret;
	}

	list_add(&ccp_alg->entry, head);

	return 0;
}