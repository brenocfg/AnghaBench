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
typedef  int /*<<< orphan*/  cf_salsa20_ctx ;

/* Variables and functions */
 int /*<<< orphan*/  cf_salsa20_cipher (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  cf_salsa20_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void salsa20_test(void)
{
  uint8_t key[32] = { 0 };
  uint8_t nonce[8] = { 0 };
  uint8_t msg[64] = { 0 };
  uint8_t cipher[64] = { 0 };

  cf_salsa20_ctx ctx;
  cf_salsa20_init(&ctx, key, sizeof key, nonce);
  cf_salsa20_cipher(&ctx, msg, cipher, sizeof msg);
}