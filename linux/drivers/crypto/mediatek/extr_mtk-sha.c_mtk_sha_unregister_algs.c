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
 int /*<<< orphan*/  crypto_unregister_ahash (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void mtk_sha_unregister_algs(void)
{
	int i;

	for (i = 0; i < ARRAY_SIZE(algs_sha1_sha224_sha256); i++)
		crypto_unregister_ahash(&algs_sha1_sha224_sha256[i]);

	for (i = 0; i < ARRAY_SIZE(algs_sha384_sha512); i++)
		crypto_unregister_ahash(&algs_sha384_sha512[i]);
}