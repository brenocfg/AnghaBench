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
 int crypto_register_acomp (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  crypto_unregister_acomp (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hisi_zip_acomp_gzip ; 
 int /*<<< orphan*/  hisi_zip_acomp_zlib ; 
 int /*<<< orphan*/  pr_err (char*) ; 

int hisi_zip_register_to_crypto(void)
{
	int ret = 0;

	ret = crypto_register_acomp(&hisi_zip_acomp_zlib);
	if (ret) {
		pr_err("Zlib acomp algorithm registration failed\n");
		return ret;
	}

	ret = crypto_register_acomp(&hisi_zip_acomp_gzip);
	if (ret) {
		pr_err("Gzip acomp algorithm registration failed\n");
		crypto_unregister_acomp(&hisi_zip_acomp_zlib);
	}

	return ret;
}