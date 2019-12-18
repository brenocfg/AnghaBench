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
typedef  int /*<<< orphan*/  cf_aes_context ;

/* Variables and functions */
 int /*<<< orphan*/  aead_aad ; 
 int /*<<< orphan*/  aead_cipher ; 
 int /*<<< orphan*/  aead_key ; 
 int /*<<< orphan*/  aead_msg ; 
 int /*<<< orphan*/  aead_nonce ; 
 int /*<<< orphan*/  aead_tag ; 
 int /*<<< orphan*/  bracket ; 
 int /*<<< orphan*/  cf_aes ; 
 int /*<<< orphan*/  cf_aes_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  cf_gcm_encrypt (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void aeadperf_aes128gcm(void)
{
  cf_aes_context ctx;
  cf_aes_init(&ctx, aead_key, 16);

  cf_gcm_encrypt(&cf_aes, &ctx,
                 aead_msg, bracket,
                 aead_aad, sizeof aead_aad,
                 aead_nonce, 12,
                 aead_cipher,
                 aead_tag, 16);
}