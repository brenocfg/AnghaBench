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
 int crypto_register_alg (int /*<<< orphan*/ *) ; 
 int crypto_register_scomp (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  crypto_unregister_alg (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  crypto_unregister_scomp (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zip_comp_deflate ; 
 int /*<<< orphan*/  zip_comp_lzs ; 
 int /*<<< orphan*/  zip_err (char*) ; 
 int /*<<< orphan*/  zip_scomp_deflate ; 
 int /*<<< orphan*/  zip_scomp_lzs ; 

__attribute__((used)) static int zip_register_compression_device(void)
{
	int ret;

	ret = crypto_register_alg(&zip_comp_deflate);
	if (ret < 0) {
		zip_err("Deflate algorithm registration failed\n");
		return ret;
	}

	ret = crypto_register_alg(&zip_comp_lzs);
	if (ret < 0) {
		zip_err("LZS algorithm registration failed\n");
		goto err_unregister_alg_deflate;
	}

	ret = crypto_register_scomp(&zip_scomp_deflate);
	if (ret < 0) {
		zip_err("Deflate scomp algorithm registration failed\n");
		goto err_unregister_alg_lzs;
	}

	ret = crypto_register_scomp(&zip_scomp_lzs);
	if (ret < 0) {
		zip_err("LZS scomp algorithm registration failed\n");
		goto err_unregister_scomp_deflate;
	}

	return ret;

err_unregister_scomp_deflate:
	crypto_unregister_scomp(&zip_scomp_deflate);
err_unregister_alg_lzs:
	crypto_unregister_alg(&zip_comp_lzs);
err_unregister_alg_deflate:
	crypto_unregister_alg(&zip_comp_deflate);

	return ret;
}