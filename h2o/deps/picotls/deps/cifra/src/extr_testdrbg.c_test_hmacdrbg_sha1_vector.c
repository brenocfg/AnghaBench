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
 int /*<<< orphan*/  cf_sha1 ; 
 scalar_t__ memcmp (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  unhex (int /*<<< orphan*/ *,int,char*) ; 

__attribute__((used)) static void test_hmacdrbg_sha1_vector(void)
{
  uint8_t entropy[16], nonce[8], reseed[16], got[80], expect[80];

  /* HMAC_DRBG.rsp, line 8. */
  unhex(entropy, sizeof entropy, "79349bbf7cdda5799557866621c91383");
  unhex(nonce, sizeof nonce, "1146733abf8c35c8");
  unhex(reseed, sizeof reseed, "c7215b5b96c48e9b338c74e3e99dfedf");
  unhex(expect, sizeof expect, "c6a16ab8d420706f0f34ab7fec5adca9d8ca3a133e159ca6ac43c6f8a2be22834a4c0a0affb10d7194f1c1a5cf7322ec1ae0964ed4bf122746e087fdb5b3e91b3493d5bb98faed49e85f130fc8a459b7");

  cf_hmac_drbg ctx;
  cf_hmac_drbg_init(&ctx, &cf_sha1, entropy, sizeof entropy, nonce, sizeof nonce, NULL, 0);
  cf_hmac_drbg_reseed(&ctx, reseed, sizeof reseed, NULL, 0);
  cf_hmac_drbg_gen(&ctx, got, sizeof got);
  cf_hmac_drbg_gen(&ctx, got, sizeof got);
  TEST_CHECK(memcmp(got, expect, sizeof got) == 0);
}