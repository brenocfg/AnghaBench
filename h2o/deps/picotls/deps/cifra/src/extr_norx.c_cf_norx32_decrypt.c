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
typedef  int /*<<< orphan*/  norx32_ctx ;

/* Variables and functions */
 int /*<<< orphan*/  decrypt_body (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  do_header (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,size_t) ; 
 int /*<<< orphan*/  do_trailer (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,size_t) ; 
 int /*<<< orphan*/  get_tag (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  init (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  mem_clean (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  mem_eq (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int) ; 

int cf_norx32_decrypt(const uint8_t key[16],
                      const uint8_t nonce[8],
                      const uint8_t *header, size_t nheader,
                      const uint8_t *ciphertext, size_t nbytes,
                      const uint8_t *trailer, size_t ntrailer,
                      const uint8_t tag[16],
                      uint8_t *plaintext)
{
  norx32_ctx ctx;
  uint8_t ourtag[16];

  init(&ctx, key, nonce);
  do_header(&ctx, header, nheader);
  decrypt_body(&ctx, ciphertext, plaintext, nbytes);
  do_trailer(&ctx, trailer, ntrailer);
  get_tag(&ctx, ourtag);

  int err = 0;

  if (!mem_eq(ourtag, tag, sizeof ourtag))
  {
    err = 1;
    mem_clean(plaintext, nbytes);
    mem_clean(ourtag, sizeof ourtag);
  }

  mem_clean(&ctx, sizeof ctx);
  return err;
}