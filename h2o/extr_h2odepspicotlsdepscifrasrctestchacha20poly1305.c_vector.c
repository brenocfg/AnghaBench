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
 int /*<<< orphan*/  assert (int) ; 
 int cf_chacha20poly1305_decrypt (int*,int*,int*,size_t,int*,size_t,int*,int*) ; 
 int /*<<< orphan*/  cf_chacha20poly1305_encrypt (int*,int*,int*,size_t,int*,size_t,int*,int*) ; 
 scalar_t__ memcmp (int*,int*,size_t) ; 
 size_t unhex (int*,int,char const*) ; 

__attribute__((used)) static void vector(const char *keystr,
                   const char *noncestr,
                   const char *headerstr,
                   const char *plainstr,
                   const char *cipherstr,
                   const char *tagstr)
{
  /* inputs */
  uint8_t K[32], N[12], H[12], A[16];
  uint8_t C[265], P[265];

  unhex(K, sizeof K, keystr);
  unhex(N, sizeof N, noncestr);
  size_t headerlen = unhex(H, sizeof H, headerstr);
  size_t plainlen  = unhex(P, sizeof P, plainstr);
  size_t cipherlen = unhex(C, sizeof C, cipherstr);
  unhex(A, sizeof A, tagstr);

  assert(cipherlen == plainlen);

  /* working data */
  uint8_t out[265], ourtag[16];

  /* check encryption works. */
  cf_chacha20poly1305_encrypt(K, N,
                              H, headerlen,
                              P, plainlen,
                              out, ourtag);

  TEST_CHECK(memcmp(out, C, cipherlen) == 0);
  TEST_CHECK(memcmp(ourtag, A, sizeof A) == 0);

  /* proper decryption */
  TEST_CHECK(0 == cf_chacha20poly1305_decrypt(K, N,
                                              H, headerlen,
                                              C, cipherlen,
                                              A, out));
  TEST_CHECK(0 == memcmp(out, P, plainlen));

  /* failure decryption */
  C[0] ^= 0xff;

  TEST_CHECK(1 == cf_chacha20poly1305_decrypt(K, N,
                                              H, headerlen,
                                              C, cipherlen,
                                              A, out));
}