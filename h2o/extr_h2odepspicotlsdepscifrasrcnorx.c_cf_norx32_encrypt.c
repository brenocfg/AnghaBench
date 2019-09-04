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
 int /*<<< orphan*/  do_header (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,size_t) ; 
 int /*<<< orphan*/  do_trailer (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,size_t) ; 
 int /*<<< orphan*/  encrypt_body (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  get_tag (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  init (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  mem_clean (int /*<<< orphan*/ *,int) ; 

void cf_norx32_encrypt(const uint8_t key[16],
                       const uint8_t nonce[8],
                       const uint8_t *header, size_t nheader,
                       const uint8_t *plaintext, size_t nbytes,
                       const uint8_t *trailer, size_t ntrailer,
                       uint8_t *ciphertext,
                       uint8_t tag[16])
{
  norx32_ctx ctx;

  init(&ctx, key, nonce);
  do_header(&ctx, header, nheader);
  encrypt_body(&ctx, plaintext, ciphertext, nbytes);
  do_trailer(&ctx, trailer, ntrailer);
  get_tag(&ctx, tag);

  mem_clean(&ctx, sizeof ctx);
}