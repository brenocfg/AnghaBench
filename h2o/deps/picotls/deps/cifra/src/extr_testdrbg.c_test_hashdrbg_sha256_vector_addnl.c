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
 int /*<<< orphan*/  cf_hash_drbg_sha256_gen_additional (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  cf_hash_drbg_sha256_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cf_hash_drbg_sha256_reseed (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int) ; 
 scalar_t__ memcmp (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  unhex (int /*<<< orphan*/ *,int,char*) ; 

__attribute__((used)) static void test_hashdrbg_sha256_vector_addnl(void)
{
  uint8_t entropy[32], nonce[16], reseed[32], got[128], expect[128], addnl[32];

  /* Hash_DRBG.rsp, line 5230. No personlisation string, but with additional data. */
  unhex(entropy, sizeof entropy, "9cfb7ad03be487a3b42be06e9ae44f283c2b1458cec801da2ae6532fcb56cc4c");
  unhex(nonce, sizeof nonce, "a20765538e8db31295747ec922c13a69");
  unhex(reseed, sizeof reseed, "96bc8014f90ebdf690db0e171b59cc46c75e2e9b8e1dc699c65c03ceb2f4d7dc");
  unhex(expect, sizeof expect, "71c1154a2a7a3552413970bf698aa02f14f8ea95e861f801f463be27868b1b14b1b4babd9eba5915a6414ab1104c8979b1918f3094925aeab0d07d2037e613b63cbd4f79d9f95c84b47ed9b77230a57515c211f48f4af6f5edb2c308b33905db308cf88f552c8912c49b34e66c026e67b302ca65b187928a1aba9a49edbfe190");

  cf_hash_drbg_sha256 ctx;
  cf_hash_drbg_sha256_init(&ctx, entropy, sizeof entropy, nonce, sizeof nonce, NULL, 0);
  unhex(addnl, sizeof addnl, "6fea0894052dab3c44d503950c7c72bd7b87de87cb81d3bb51c32a62f742286d");
  cf_hash_drbg_sha256_reseed(&ctx, reseed, sizeof reseed, addnl, sizeof addnl);
  unhex(addnl, sizeof addnl, "d3467c78563b74c13db7af36c2a964820f2a9b1b167474906508fdac9b2049a6");
  cf_hash_drbg_sha256_gen_additional(&ctx, addnl, sizeof addnl, got, sizeof got);
  unhex(addnl, sizeof addnl, "5840a11cc9ebf77b963854726a826370ffdb2fc2b3d8479e1df5dcfa3dddd10b");
  cf_hash_drbg_sha256_gen_additional(&ctx, addnl, sizeof addnl, got, sizeof got);
  TEST_CHECK(memcmp(got, expect, sizeof got) == 0);
}