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

/* Variables and functions */
 int ARRAY_SIZE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * aes_algs ; 
 int /*<<< orphan*/  aes_gcm_alg ; 
 int crypto_register_aead (int /*<<< orphan*/ *) ; 
 int crypto_register_alg (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  crypto_unregister_alg (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int mtk_aes_register_algs(void)
{
	int err, i;

	for (i = 0; i < ARRAY_SIZE(aes_algs); i++) {
		err = crypto_register_alg(&aes_algs[i]);
		if (err)
			goto err_aes_algs;
	}

	err = crypto_register_aead(&aes_gcm_alg);
	if (err)
		goto err_aes_algs;

	return 0;

err_aes_algs:
	for (; i--; )
		crypto_unregister_alg(&aes_algs[i]);

	return err;
}