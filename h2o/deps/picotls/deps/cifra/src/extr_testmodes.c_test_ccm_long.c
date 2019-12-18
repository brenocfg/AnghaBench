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
typedef  int /*<<< orphan*/  cf_aes_context ;

/* Variables and functions */
 int /*<<< orphan*/  TEST_CHECK (int) ; 
 int /*<<< orphan*/  cf_aes ; 
 int /*<<< orphan*/  cf_aes_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  cf_ccm_encrypt (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  fill (int /*<<< orphan*/ *,int,int) ; 
 scalar_t__ memcmp (void const*,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void test_ccm_long(void)
{
  /* This is example 4 from SP800-38C, to test the long AAD code path. */
  uint8_t header[0x10000];
  uint8_t key[16];
  uint8_t tag[14];
  uint8_t nonce[13];
  uint8_t plain[32], cipher[32];

  fill(header, sizeof header, 0x00);
  fill(key, sizeof key, 0x40);
  fill(nonce, sizeof nonce, 0x10);
  fill(plain, sizeof plain, 0x20);

  const void *expect_tag = "\xb4\xac\x6b\xec\x93\xe8\x59\x8e\x7f\x0d\xad\xbc\xea\x5b";
  const void *expect_cipher = "\x69\x91\x5d\xad\x1e\x84\xc6\x37\x6a\x68\xc2\x96\x7e\x4d\xab\x61\x5a\xe0\xfd\x1f\xae\xc4\x4c\xc4\x84\x82\x85\x29\x46\x3c\xcf\x72";

  cf_aes_context ctx;
  cf_aes_init(&ctx, key, sizeof key);

  cf_ccm_encrypt(&cf_aes, &ctx,
                 plain, sizeof plain, 15 - sizeof nonce,
                 header, sizeof header,
                 nonce, sizeof nonce,
                 cipher,
                 tag, sizeof tag);

  TEST_CHECK(memcmp(expect_tag, tag, sizeof tag) == 0);
  TEST_CHECK(memcmp(expect_cipher, cipher, sizeof cipher) == 0);
}