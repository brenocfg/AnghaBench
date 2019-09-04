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
typedef  int /*<<< orphan*/  cf_chacha20_ctx ;

/* Variables and functions */
 int /*<<< orphan*/  TEST_CHECK (int) ; 
 int /*<<< orphan*/  cf_chacha20_cipher (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  cf_chacha20_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 
 scalar_t__ memcmp (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  unhex (int /*<<< orphan*/ *,int,char*) ; 

__attribute__((used)) static void test_chacha20(void)
{
  uint8_t key[32], nonce[8], block[256], expect[256];

  unhex(key, 32, "000102030405060708090a0b0c0d0e0f101112131415161718191a1b1c1d1e1f");
  unhex(nonce, 8, "0001020304050607");
  unhex(expect, 256, "f798a189f195e66982105ffb640bb7757f579da31602fc93ec01ac56f85ac3c134a4547b733b46413042c9440049176905d3be59ea1c53f15916155c2be8241a38008b9a26bc35941e2444177c8ade6689de95264986d95889fb60e84629c9bd9a5acb1cc118be563eb9b3a4a472f82e09a7e778492b562ef7130e88dfe031c79db9d4f7c7a899151b9a475032b63fc385245fe054e3dd5a97a5f576fe064025d3ce042c566ab2c507b138db853e3d6959660996546cc9c4a6eafdc777c040d70eaf46f76dad3979e5c5360c3317166a1c894c94a371876a94df7628fe4eaaf2ccb27d5aaae0ad7ad0f9d4b6ad3b54098746d4524d38407a6deb3ab78fab78c9");
  memset(block, 0, 256);

  cf_chacha20_ctx ctx;
  cf_chacha20_init(&ctx, key, sizeof key, nonce);
  cf_chacha20_cipher(&ctx, block, block, sizeof block);

  TEST_CHECK(memcmp(expect, block, sizeof expect) == 0);

  /* Check 128-bit mode works. */
  cf_chacha20_init(&ctx, key, 16, nonce);
  cf_chacha20_cipher(&ctx, block, block, sizeof block);
}