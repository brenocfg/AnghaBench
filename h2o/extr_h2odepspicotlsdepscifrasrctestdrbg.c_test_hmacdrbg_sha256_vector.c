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
typedef  int /*<<< orphan*/  cf_hmac_drbg ;

/* Variables and functions */
 int /*<<< orphan*/  TEST_CHECK (int) ; 
 int /*<<< orphan*/  cf_hmac_drbg_gen (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  cf_hmac_drbg_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cf_hmac_drbg_reseed (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cf_sha256 ; 
 scalar_t__ memcmp (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  unhex (int /*<<< orphan*/ *,int,char*) ; 

__attribute__((used)) static void test_hmacdrbg_sha256_vector(void)
{
  uint8_t entropy[32], nonce[16], reseed[32], got[128], expect[128];

  /* HMAC_DRBG.rsp, line 5064. */
  unhex(entropy, sizeof entropy, "06032cd5eed33f39265f49ecb142c511da9aff2af71203bffaf34a9ca5bd9c0d");
  unhex(nonce, sizeof nonce, "0e66f71edc43e42a45ad3c6fc6cdc4df");
  unhex(reseed, sizeof reseed, "01920a4e669ed3a85ae8a33b35a74ad7fb2a6bb4cf395ce00334a9c9a5a5d552");
  unhex(expect, sizeof expect, "76fc79fe9b50beccc991a11b5635783a83536add03c157fb30645e611c2898bb2b1bc215000209208cd506cb28da2a51bdb03826aaf2bd2335d576d519160842e7158ad0949d1a9ec3e66ea1b1a064b005de914eac2e9d4f2d72a8616a80225422918250ff66a41bd2f864a6a38cc5b6499dc43f7f2bd09e1e0f8f5885935124");

  cf_hmac_drbg ctx;
  cf_hmac_drbg_init(&ctx, &cf_sha256, entropy, sizeof entropy, nonce, sizeof nonce, NULL, 0);
  cf_hmac_drbg_reseed(&ctx, reseed, sizeof reseed, NULL, 0);
  cf_hmac_drbg_gen(&ctx, got, sizeof got);
  cf_hmac_drbg_gen(&ctx, got, sizeof got);
  TEST_CHECK(memcmp(got, expect, sizeof got) == 0);
}