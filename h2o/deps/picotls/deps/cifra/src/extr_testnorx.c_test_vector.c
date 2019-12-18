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
typedef  int uint8_t ;

/* Variables and functions */
 int /*<<< orphan*/  TEST_CHECK (int) ; 
 int cf_norx32_decrypt (int*,int*,int*,int,int*,int,int*,int,int*,int*) ; 
 int /*<<< orphan*/  cf_norx32_encrypt (int*,int*,int*,int,int*,int,int*,int,int*,int*) ; 
 scalar_t__ memcmp (int*,int*,int) ; 
 int /*<<< orphan*/  unhex (int*,int,char*) ; 

__attribute__((used)) static void test_vector(void)
{
  uint8_t K[16], N[8], A[128], M[128], Z[128], C[128], T[16];

  /* This is from the v2.0 paper, section A.2. */

  unhex(K, sizeof K, "000102030405060708090a0b0c0d0e0f");
  unhex(N, sizeof N, "f0e0d0c0b0a09080");

  for (unsigned i = 0; i < 128; i++)
  {
    A[i] = M[i] = Z[i] = i;
  }

  cf_norx32_encrypt(K, N,
                    A, sizeof A,
                    M, sizeof M,
                    Z, sizeof Z,
                    C, T);

  uint8_t expect_C[128], expect_T[16];

  unhex(expect_C, sizeof expect_C, "f4afc8e66d2d80de0a7f719c899624c9ad896ec7c61739d5376d0648c7bcb204e57db05c6f83b3ff4315e8a4ef2f2c855f21ea4c51ac6de575773ba548f36e636a13b979d953bb91298ea4a6e2aa27402991e0da541997825407b2f12441de3ae6c5dbfe41b12f1480d234832765111e4c09deef9fe3971618d2217c4b77921e");
  unhex(expect_T, sizeof expect_T, "7810131eea2eab1e5da05d23d4e3cb99");

  TEST_CHECK(memcmp(C, expect_C, sizeof C) == 0);
  TEST_CHECK(memcmp(T, expect_T, sizeof T) == 0);

  uint8_t M2[128];
  TEST_CHECK(0 ==
             cf_norx32_decrypt(K, N,
                               A, sizeof A,
                               C, sizeof C,
                               Z, sizeof Z,
                               T,
                               M2));

  TEST_CHECK(memcmp(M, M2, sizeof M) == 0);
  T[0] ^= 0xff;

  TEST_CHECK(cf_norx32_decrypt(K, N,
                               A, sizeof A,
                               C, sizeof C,
                               Z, sizeof Z,
                               T,
                               M2));
}