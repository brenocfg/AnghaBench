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
typedef  int /*<<< orphan*/  cf_aes_context ;

/* Variables and functions */
 int /*<<< orphan*/  TEST_CHECK (int) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  cf_aes ; 
 int /*<<< orphan*/  cf_aes_init (int /*<<< orphan*/ *,void const*,size_t) ; 
 int cf_ocb_decrypt (int /*<<< orphan*/ *,int /*<<< orphan*/ *,void const*,size_t,void const*,size_t,void const*,size_t,int*,size_t,int*) ; 
 int /*<<< orphan*/  cf_ocb_encrypt (int /*<<< orphan*/ *,int /*<<< orphan*/ *,void const*,size_t,void const*,size_t,void const*,size_t,int*,int*,size_t) ; 
 scalar_t__ memcmp (int*,void const*,size_t) ; 

__attribute__((used)) static void check_ocb(const void *key, size_t nkey,
                      const void *header, size_t nheader,
                      const void *plain, size_t nplain,
                      const void *nonce, size_t nnonce,
                      const void *expect_cipher, size_t ncipher,
                      const void *expect_tag, size_t ntag)
{
  uint8_t cipher[40], tag[16];

  assert(ncipher == nplain);
  assert(ncipher <= sizeof cipher);
  assert(ntag <= sizeof tag);

  cf_aes_context ctx;
  cf_aes_init(&ctx, key, nkey);

  cf_ocb_encrypt(&cf_aes, &ctx,
                 plain, nplain,
                 header, nheader,
                 nonce, nnonce,
                 cipher,
                 tag, ntag);

  TEST_CHECK(memcmp(tag, expect_tag, ntag) == 0);
  TEST_CHECK(memcmp(cipher, expect_cipher, ncipher) == 0);

  uint8_t decrypted[40];
  int err;
  err = cf_ocb_decrypt(&cf_aes, &ctx,
                       expect_cipher, ncipher,
                       header, nheader,
                       nonce, nnonce,
                       tag, ntag,
                       decrypted);
  TEST_CHECK(err == 0);
  TEST_CHECK(memcmp(decrypted, plain, nplain) == 0);

  tag[0] ^= 0xff;

  err = cf_ocb_decrypt(&cf_aes, &ctx,
                       expect_cipher, ncipher,
                       header, nheader,
                       nonce, nnonce,
                       tag, ntag,
                       decrypted);
  TEST_CHECK(err == 1);
}