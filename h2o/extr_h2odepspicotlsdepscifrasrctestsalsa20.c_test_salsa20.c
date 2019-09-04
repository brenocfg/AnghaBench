#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_4__ {int /*<<< orphan*/ * nonce; } ;
typedef  TYPE_1__ cf_salsa20_ctx ;

/* Variables and functions */
 int /*<<< orphan*/  TEST_CHECK (int) ; 
 int /*<<< orphan*/  cf_salsa20_cipher (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  cf_salsa20_init (TYPE_1__*,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 
 scalar_t__ memcmp (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  unhex (int /*<<< orphan*/ *,int,char*) ; 

__attribute__((used)) static void test_salsa20(void)
{
  cf_salsa20_ctx ctx;
  uint8_t key[32], nonce[8], cipher[64], expect[64];

  unhex(key, 32, "0102030405060708090a0b0c0d0e0f10c9cacbcccdcecfd0d1d2d3d4d5d6d7d8");
  memset(nonce, 0, 8);

  cf_salsa20_init(&ctx, key, sizeof key, nonce);
  unhex(ctx.nonce, 16, "65666768696a6b6c6d6e6f7071727374");
  memset(cipher, 0, 64);
  cf_salsa20_cipher(&ctx, cipher, cipher, 64);

  unhex(expect, 64, "45254427290f6bc1ff8b7a06aae9d9625990b66a1533c841ef31de22d772287e68c507e1c5991f02664e4cb054f5f6b8b1a0858206489577c0c384ecea67f64a");
  TEST_CHECK(memcmp(expect, cipher, 64) == 0);

  cf_salsa20_init(&ctx, key, 16, nonce);
  unhex(ctx.nonce, 16, "65666768696a6b6c6d6e6f7071727374");
  memset(cipher, 0, 64);
  cf_salsa20_cipher(&ctx, cipher, cipher, 64);

  unhex(expect, 64, "27ad2ef81ec852113043feef25120df7f1c83d900a3732b9062ff6fd8f56bbe186556ef6a1a32bebe75eab3391d6701d0ee80510978cb78dab097ab568b6b1c1");
  TEST_CHECK(memcmp(expect, cipher, 64) == 0);
}