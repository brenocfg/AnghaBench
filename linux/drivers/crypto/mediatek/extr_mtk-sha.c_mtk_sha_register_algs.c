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
 int /*<<< orphan*/ * algs_sha1_sha224_sha256 ; 
 int /*<<< orphan*/ * algs_sha384_sha512 ; 
 int crypto_register_ahash (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  crypto_unregister_ahash (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int mtk_sha_register_algs(void)
{
	int err, i;

	for (i = 0; i < ARRAY_SIZE(algs_sha1_sha224_sha256); i++) {
		err = crypto_register_ahash(&algs_sha1_sha224_sha256[i]);
		if (err)
			goto err_sha_224_256_algs;
	}

	for (i = 0; i < ARRAY_SIZE(algs_sha384_sha512); i++) {
		err = crypto_register_ahash(&algs_sha384_sha512[i]);
		if (err)
			goto err_sha_384_512_algs;
	}

	return 0;

err_sha_384_512_algs:
	for (; i--; )
		crypto_unregister_ahash(&algs_sha384_sha512[i]);
	i = ARRAY_SIZE(algs_sha1_sha224_sha256);
err_sha_224_256_algs:
	for (; i--; )
		crypto_unregister_ahash(&algs_sha1_sha224_sha256[i]);

	return err;
}