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
 int /*<<< orphan*/  cf_chacha20_core (int*,int*,int*,int const*,int*) ; 
 scalar_t__ memcmp (int*,int*,int) ; 
 int /*<<< orphan*/  memset (int*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  unhex (int*,int,char*) ; 

__attribute__((used)) static void test_chacha20_core(void)
{
  uint8_t k0[16], k1[16], nonce[16], out[64], expect[64];

  /* From draft-agl-tls-chacha20poly1305-04 section 7. */

  memset(k0, 0, sizeof k0);
  memset(k1, 0, sizeof k1);
  memset(nonce, 0, sizeof nonce);

  cf_chacha20_core(k0, k1, nonce, (const uint8_t *) "expand 32-byte k", out);

  unhex(expect, 60, "76b8e0ada0f13d90405d6ae55386bd28bdd219b8a08ded1aa836efcc8b770dc7da41597c5157488d7724e03fb8d84a376a43b8f41518a11cc387b669");
  TEST_CHECK(memcmp(expect, out, 60) == 0);

  k1[15] = 0x01;
  cf_chacha20_core(k0, k1, nonce, (const uint8_t *) "expand 32-byte k", out);

  unhex(expect, 60, "4540f05a9f1fb296d7736e7b208e3c96eb4fe1834688d2604f450952ed432d41bbe2a0b6ea7566d2a5d1e7e20d42af2c53d792b1c43fea817e9ad275");
  TEST_CHECK(memcmp(expect, out, 60) == 0);

  memset(k1, 0, sizeof k1);
  nonce[15] = 0x01;

  cf_chacha20_core(k0, k1, nonce, (const uint8_t *) "expand 32-byte k", out);

  unhex(expect, 60, "de9cba7bf3d69ef5e786dc63973f653a0b49e015adbff7134fcb7df137821031e85a050278a7084527214f73efc7fa5b5277062eb7a0433e445f41e3");
  TEST_CHECK(memcmp(expect, out, 60) == 0);

  memset(nonce, 0, sizeof nonce);
  nonce[8] = 0x01;
  
  cf_chacha20_core(k0, k1, nonce, (const uint8_t *) "expand 32-byte k", out);

  unhex(expect, 64, "ef3fdfd6c61578fbf5cf35bd3dd33b8009631634d21e42ac33960bd138e50d32111e4caf237ee53ca8ad6426194a88545ddc497a0b466e7d6bbdb0041b2f586b");
  TEST_CHECK(memcmp(expect, out, 64) == 0);

  unhex(k0, 16, "000102030405060708090a0b0c0d0e0f");
  unhex(k1, 16, "101112131415161718191a1b1c1d1e1f");
  unhex(nonce, 16, "00000000000000000001020304050607");

  cf_chacha20_core(k0, k1, nonce, (const uint8_t *) "expand 32-byte k", out);

  unhex(expect, 64, "f798a189f195e66982105ffb640bb7757f579da31602fc93ec01ac56f85ac3c134a4547b733b46413042c9440049176905d3be59ea1c53f15916155c2be8241a");
  TEST_CHECK(memcmp(expect, out, 64) == 0);
  
  nonce[0]++;
  cf_chacha20_core(k0, k1, nonce, (const uint8_t *) "expand 32-byte k", out);
  
  unhex(expect, 64, "38008b9a26bc35941e2444177c8ade6689de95264986d95889fb60e84629c9bd9a5acb1cc118be563eb9b3a4a472f82e09a7e778492b562ef7130e88dfe031c7");
  TEST_CHECK(memcmp(expect, out, 64) == 0);

  nonce[0]++;
  cf_chacha20_core(k0, k1, nonce, (const uint8_t *) "expand 32-byte k", out);
  
  unhex(expect, 64, "9db9d4f7c7a899151b9a475032b63fc385245fe054e3dd5a97a5f576fe064025d3ce042c566ab2c507b138db853e3d6959660996546cc9c4a6eafdc777c040d7");
  TEST_CHECK(memcmp(expect, out, 64) == 0);

  nonce[0]++;
  cf_chacha20_core(k0, k1, nonce, (const uint8_t *) "expand 32-byte k", out);

  unhex(expect, 64, "0eaf46f76dad3979e5c5360c3317166a1c894c94a371876a94df7628fe4eaaf2ccb27d5aaae0ad7ad0f9d4b6ad3b54098746d4524d38407a6deb3ab78fab78c9");
  TEST_CHECK(memcmp(expect, out, 64) == 0);
}