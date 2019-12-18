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
struct img_hash_dev {int dummy; } ;

/* Variables and functions */
 int ARRAY_SIZE (int /*<<< orphan*/ *) ; 
 int crypto_register_ahash (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  crypto_unregister_ahash (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * img_algs ; 

__attribute__((used)) static int img_register_algs(struct img_hash_dev *hdev)
{
	int i, err;

	for (i = 0; i < ARRAY_SIZE(img_algs); i++) {
		err = crypto_register_ahash(&img_algs[i]);
		if (err)
			goto err_reg;
	}
	return 0;

err_reg:
	for (; i--; )
		crypto_unregister_ahash(&img_algs[i]);

	return err;
}