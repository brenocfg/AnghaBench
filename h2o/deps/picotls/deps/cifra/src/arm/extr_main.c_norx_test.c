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

/* Variables and functions */
 int /*<<< orphan*/  cf_norx32_encrypt (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void norx_test(void)
{
  uint8_t key[16] = { 0 };
  uint8_t msg[16] = { 0 };
  uint8_t aad[16] = { 0 };
  uint8_t nonce[8] = { 0 };
  uint8_t cipher[16] = { 0 };
  uint8_t tag[16] = { 0 };

  cf_norx32_encrypt(key,
                    nonce,
                    aad, sizeof aad,
                    msg, sizeof msg,
                    NULL, 0,
                    cipher,
                    tag);
}