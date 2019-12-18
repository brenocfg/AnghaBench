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

/* Variables and functions */
 int /*<<< orphan*/  aead_aad ; 
 int /*<<< orphan*/  aead_cipher ; 
 int /*<<< orphan*/  aead_key ; 
 int /*<<< orphan*/  aead_msg ; 
 int /*<<< orphan*/  aead_nonce ; 
 int /*<<< orphan*/  aead_tag ; 
 int /*<<< orphan*/  bracket ; 
 int /*<<< orphan*/  cf_chacha20poly1305_encrypt (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void aeadperf_chacha20poly1305(void)
{
  cf_chacha20poly1305_encrypt(aead_key, aead_nonce,
                              aead_aad, sizeof aead_aad,
                              aead_msg, bracket,
                              aead_cipher, aead_tag);
}