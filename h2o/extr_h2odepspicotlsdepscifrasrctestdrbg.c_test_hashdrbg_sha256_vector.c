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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  cf_hash_drbg_sha256 ;

/* Variables and functions */
 int /*<<< orphan*/  TEST_CHECK (int) ; 
 int /*<<< orphan*/  cf_hash_drbg_sha256_gen (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  cf_hash_drbg_sha256_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  cf_hash_drbg_sha256_reseed (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ memcmp (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  unhex (int /*<<< orphan*/ *,int,char*) ; 

__attribute__((used)) static void test_hashdrbg_sha256_vector(void)
{
  uint8_t entropy[32], nonce[16], persn[32], reseed[32], got[128], expect[128];

  /* This is the first KAT from NIST's CAVP example
   * file for SHA-256 with all inputs used; line 4360. */
  unhex(entropy, sizeof entropy, "b87bb4de5c148d964fc0cb612d69295671780b4270fe32bf389b6f49488efe13");
  unhex(nonce, sizeof nonce, "27eb37a0c695c4ee3c9b70b7f6b33492");
  unhex(persn, sizeof persn, "52321406ac8a9c266b1f8d811bb871269e5824b59a0234f01d358193523bbb7c");
  unhex(reseed, sizeof reseed, "7638267f534c4e6ee22cc6ca6ed824fd5d3d387c00b89dd791eb5ac9766385b8");

  unhex(expect, sizeof expect, "de01c061651bab3cef2fc4ea89a56b6e86e74b2e9fd11ed671c97c813778a06a2c1f41b41e754a5257750c6bde9601da9d67d8d9564f4a8538b92516a2dacc496dee257b85393f2a01ad59aa3257f1b6da9566e3706d2d6d4a26e511b0c64d7dc223acb24827178afa43ca8d5a66f983d6929dc61564c4c14fc32d85765a23f7");

  cf_hash_drbg_sha256 ctx;
  cf_hash_drbg_sha256_init(&ctx, entropy, sizeof entropy, nonce, sizeof nonce, persn, sizeof persn);
  cf_hash_drbg_sha256_reseed(&ctx, reseed, sizeof reseed, NULL, 0);
  cf_hash_drbg_sha256_gen(&ctx, got, sizeof got);
  cf_hash_drbg_sha256_gen(&ctx, got, sizeof got);
  TEST_CHECK(memcmp(got, expect, sizeof got) == 0);

  /* This is line 5064 from Hash_DRBG.rsp */
  unhex(entropy, sizeof entropy, "63363377e41e86468deb0ab4a8ed683f6a134e47e014c700454e81e95358a569");
  unhex(nonce, sizeof nonce, "808aa38f2a72a62359915a9f8a04ca68");
  /* no persn */
  unhex(reseed, sizeof reseed, "e62b8a8ee8f141b6980566e3bfe3c04903dad4ac2cdf9f2280010a6739bc83d3");
  unhex(expect, sizeof expect, "04eec63bb231df2c630a1afbe724949d005a587851e1aa795e477347c8b056621c18bddcdd8d99fc5fc2b92053d8cfacfb0bb8831205fad1ddd6c071318a6018f03b73f5ede4d4d071f9de03fd7aea105d9299b8af99aa075bdb4db9aa28c18d174b56ee2a014d098896ff2282c955a81969e069fa8ce007a180183a07dfae17");

  cf_hash_drbg_sha256_init(&ctx, entropy, sizeof entropy, nonce, sizeof nonce, NULL, 0);
  cf_hash_drbg_sha256_reseed(&ctx, reseed, sizeof reseed, NULL, 0);
  cf_hash_drbg_sha256_gen(&ctx, got, sizeof got);
  cf_hash_drbg_sha256_gen(&ctx, got, sizeof got);
  TEST_CHECK(memcmp(got, expect, sizeof got) == 0);
}