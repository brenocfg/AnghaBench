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
 int /*<<< orphan*/  cf_hmac_drbg_gen_additional (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  cf_hmac_drbg_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cf_hmac_drbg_reseed (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  cf_sha512 ; 
 scalar_t__ memcmp (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  unhex (int /*<<< orphan*/ *,int,char*) ; 

__attribute__((used)) static void test_hmacdrbg_sha512_vector_addnl(void)
{
  uint8_t entropy[32], nonce[16], reseed[32], got[256], expect[256], addnl[32];

  /* HMAC_DRBG.rsp, line 10286. */
  unhex(entropy, sizeof entropy, "4686a959e17dfb96c294b09c0f7a60efb386416cfb4c8972bcc55e44a151607a");
  unhex(nonce, sizeof nonce, "5226543b4c89321bbfb0f11f18ee3462");
  unhex(reseed, sizeof reseed, "5ef50daaf29929047870235c17762f5df5d9ab1af656e0e215fcc6fd9fc0d85d");
  unhex(expect, sizeof expect, "b60d8803531b2b8583d17bdf3ac7c01f3c65cf9b069862b2d39b9024b34c172b712db0704acb078a1ab1aec0390dbaee2dec9be7b234e63da481fd469a92c77bc7bb2cfca586855520e0f9e9d47dcb9bdf2a2fdfa9f2b4342ef0ea582616b55477717cfd516d46d6383257743656f7cf8b38402ba795a8c9d35a4aa88bec623313dad6ead689d152b54074f183b2fee556f554db343626cea853718f18d386bc8bebb0c07b3c5e96ceb391ffceece88864dbd3be83a613562c5c417a24807d5f9332974f045e79a9ade36994af6cf9bbeeb71d0025fcb4ad50f121cbc2df7cd12ff5a50cddfd9a4bbc6d942d743c8b8fbebe00eeccea3d14e07ff8454fa715da");

  cf_hmac_drbg ctx;
  cf_hmac_drbg_init(&ctx, &cf_sha512, entropy, sizeof entropy, nonce, sizeof nonce, NULL, 0);
  unhex(addnl, sizeof addnl, "d2383c3e528492269e6c3b3aaa2b54fbf48731f5aa52150ce7fc644679a5e7c6");
  cf_hmac_drbg_reseed(&ctx, reseed, sizeof reseed, addnl, sizeof addnl);
  unhex(addnl, sizeof addnl, "c841e7a2d9d13bdb8644cd7f5d91d241a369e12dc6c9c2be50d1ed29484bff98");
  cf_hmac_drbg_gen_additional(&ctx, addnl, sizeof addnl, got, sizeof got);
  unhex(addnl, sizeof addnl, "9054cf9216af66a788d3bf6757b8987e42d4e49b325e728dc645d5e107048245");
  cf_hmac_drbg_gen_additional(&ctx, addnl, sizeof addnl, got, sizeof got);
  TEST_CHECK(memcmp(got, expect, sizeof got) == 0);
}