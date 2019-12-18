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
 int /*<<< orphan*/  cf_aes_decrypt (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cf_aes_encrypt (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cf_aes_finish (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cf_aes_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *,size_t) ; 
 scalar_t__ memcmp (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 size_t unhex (int /*<<< orphan*/ *,int,char const*) ; 

__attribute__((used)) static void vector(const char *input, const char *output,
                   const char *key)
{
  uint8_t keybuf[32], inbuf[16], outbuf[16], tmp[16];
  size_t nkey = sizeof keybuf;
  cf_aes_context ctx;

  nkey = unhex(keybuf, 32, key);
  unhex(inbuf, 16, input);
  unhex(outbuf, 16, output);

  cf_aes_init(&ctx, keybuf, nkey);
  cf_aes_encrypt(&ctx, inbuf, tmp);
  TEST_CHECK(memcmp(tmp, outbuf, 16) == 0);
  
  cf_aes_decrypt(&ctx, outbuf, tmp);
  TEST_CHECK(memcmp(tmp, inbuf, 16) == 0);
  cf_aes_finish(&ctx);
}