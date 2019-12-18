#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct device {int dummy; } ;
struct cc_drvdata {scalar_t__ hw_rev; int std_bodies; scalar_t__ sec_disabled; struct cc_cipher_handle* cipher_handle; } ;
struct TYPE_6__ {int cra_driver_name; } ;
struct TYPE_8__ {TYPE_1__ base; } ;
struct cc_crypto_alg {TYPE_3__ skcipher_alg; int /*<<< orphan*/  entry; struct cc_drvdata* drvdata; } ;
struct cc_cipher_handle {int /*<<< orphan*/  alg_list; } ;
struct TYPE_7__ {scalar_t__ min_hw_rev; int std_body; int driver_name; scalar_t__ sec_func; } ;

/* Variables and functions */
 int ARRAY_SIZE (TYPE_2__*) ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 scalar_t__ IS_ERR (struct cc_crypto_alg*) ; 
 int PTR_ERR (struct cc_crypto_alg*) ; 
 int /*<<< orphan*/  cc_cipher_free (struct cc_drvdata*) ; 
 struct cc_crypto_alg* cc_create_alg (TYPE_2__*,struct device*) ; 
 int crypto_register_skcipher (TYPE_3__*) ; 
 int /*<<< orphan*/  dev_dbg (struct device*,char*,int,...) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,int) ; 
 struct device* drvdata_to_dev (struct cc_drvdata*) ; 
 int /*<<< orphan*/  kfree (struct cc_crypto_alg*) ; 
 struct cc_cipher_handle* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 TYPE_2__* skcipher_algs ; 

int cc_cipher_alloc(struct cc_drvdata *drvdata)
{
	struct cc_cipher_handle *cipher_handle;
	struct cc_crypto_alg *t_alg;
	struct device *dev = drvdata_to_dev(drvdata);
	int rc = -ENOMEM;
	int alg;

	cipher_handle = kmalloc(sizeof(*cipher_handle), GFP_KERNEL);
	if (!cipher_handle)
		return -ENOMEM;

	INIT_LIST_HEAD(&cipher_handle->alg_list);
	drvdata->cipher_handle = cipher_handle;

	/* Linux crypto */
	dev_dbg(dev, "Number of algorithms = %zu\n",
		ARRAY_SIZE(skcipher_algs));
	for (alg = 0; alg < ARRAY_SIZE(skcipher_algs); alg++) {
		if ((skcipher_algs[alg].min_hw_rev > drvdata->hw_rev) ||
		    !(drvdata->std_bodies & skcipher_algs[alg].std_body) ||
		    (drvdata->sec_disabled && skcipher_algs[alg].sec_func))
			continue;

		dev_dbg(dev, "creating %s\n", skcipher_algs[alg].driver_name);
		t_alg = cc_create_alg(&skcipher_algs[alg], dev);
		if (IS_ERR(t_alg)) {
			rc = PTR_ERR(t_alg);
			dev_err(dev, "%s alg allocation failed\n",
				skcipher_algs[alg].driver_name);
			goto fail0;
		}
		t_alg->drvdata = drvdata;

		dev_dbg(dev, "registering %s\n",
			skcipher_algs[alg].driver_name);
		rc = crypto_register_skcipher(&t_alg->skcipher_alg);
		dev_dbg(dev, "%s alg registration rc = %x\n",
			t_alg->skcipher_alg.base.cra_driver_name, rc);
		if (rc) {
			dev_err(dev, "%s alg registration failed\n",
				t_alg->skcipher_alg.base.cra_driver_name);
			kfree(t_alg);
			goto fail0;
		} else {
			list_add_tail(&t_alg->entry,
				      &cipher_handle->alg_list);
			dev_dbg(dev, "Registered %s\n",
				t_alg->skcipher_alg.base.cra_driver_name);
		}
	}
	return 0;

fail0:
	cc_cipher_free(drvdata);
	return rc;
}