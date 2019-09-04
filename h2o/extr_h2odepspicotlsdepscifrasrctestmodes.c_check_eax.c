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
 int cf_eax_decrypt (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int*,size_t,void const*,size_t,void const*,size_t,int*,size_t,int*) ; 
 int /*<<< orphan*/  cf_eax_encrypt (int /*<<< orphan*/ *,int /*<<< orphan*/ *,void const*,size_t,void const*,size_t,void const*,size_t,int*,int*,size_t) ; 
 scalar_t__ memcmp (int*,void const*,size_t) ; 

__attribute__((used)) static void check_eax(const void *key, size_t nkey,
                      const void *msg, size_t nmsg,
                      const void *nonce, size_t nnonce,
                      const void *header, size_t nheader,
                      const void *expect_cipher,
                      const void *expect_tag, size_t ntag)
{
  uint8_t cipher[32];
  uint8_t tag[16];

  assert(nmsg <= sizeof cipher);
  assert(ntag <= ntag);

  cf_aes_context aes;
  cf_aes_init(&aes, key, nkey);

  cf_eax_encrypt(&cf_aes, &aes,
                 msg, nmsg,
                 header, nheader,
                 nonce, nnonce,
                 cipher,
                 tag, ntag);

  TEST_CHECK(memcmp(expect_cipher, cipher, nmsg) == 0);
  TEST_CHECK(memcmp(expect_tag, tag, ntag) == 0);

  int rc;
  uint8_t tmp[sizeof cipher];
  rc = cf_eax_decrypt(&cf_aes, &aes,
                      cipher, nmsg,
                      header, nheader,
                      nonce, nnonce,
                      tag, ntag,
                      tmp);
  TEST_CHECK(rc == 0);
  TEST_CHECK(memcmp(tmp, msg, nmsg) == 0);

  tag[0] ^= 0xff;
  rc = cf_eax_decrypt(&cf_aes, &aes,
                      cipher, nmsg,
                      header, nheader,
                      nonce, nnonce,
                      tag, ntag,
                      tmp);
  TEST_CHECK(rc == 1);
}