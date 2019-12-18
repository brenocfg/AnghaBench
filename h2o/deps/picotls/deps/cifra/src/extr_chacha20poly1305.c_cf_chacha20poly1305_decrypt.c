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
 int /*<<< orphan*/  DECRYPT ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int) ; 
 int process (int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,size_t,int /*<<< orphan*/  const*,size_t,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

int cf_chacha20poly1305_decrypt(const uint8_t key[32],
                                const uint8_t nonce[12],
                                const uint8_t *header, size_t nheader,
                                const uint8_t *ciphertext, size_t nbytes,
                                const uint8_t tag[16],
                                uint8_t *plaintext)
{
  uint8_t ourtag[16];
  memcpy(ourtag, tag, sizeof ourtag);

  return process(key,
                 nonce,
                 header, nheader,
                 ciphertext, nbytes,
                 plaintext,
                 DECRYPT,
                 ourtag);
}