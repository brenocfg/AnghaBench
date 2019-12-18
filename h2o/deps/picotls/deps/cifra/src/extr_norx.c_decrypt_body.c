#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8_t ;
struct TYPE_6__ {int /*<<< orphan*/ * s; } ;
typedef  TYPE_1__ norx32_ctx ;

/* Variables and functions */
 int /*<<< orphan*/  DOMAIN_PAYLOAD ; 
 size_t RATE_BYTES ; 
 size_t RATE_WORDS ; 
 size_t WORD_BYTES ; 
 int /*<<< orphan*/  body_block_decrypt (TYPE_1__*,int const*,int*,size_t,size_t) ; 
 int /*<<< orphan*/  read32_le (int*) ; 
 int /*<<< orphan*/  switch_domain (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  undo_padding (TYPE_1__*,size_t) ; 
 int /*<<< orphan*/  write32_le (int /*<<< orphan*/ ,int*) ; 

__attribute__((used)) static void decrypt_body(norx32_ctx *ctx,
                         const uint8_t *cipher, uint8_t *plain, size_t nbytes)
{
  if (nbytes == 0)
    return;

  /* Process full blocks. */
  while (nbytes >= RATE_BYTES)
  {
    switch_domain(ctx, DOMAIN_PAYLOAD);
    body_block_decrypt(ctx, cipher, plain, 0, RATE_WORDS);
    plain += RATE_BYTES;
    cipher += RATE_BYTES;
    nbytes -= RATE_BYTES;
  }

  /* Then partial blocks. */
  size_t offset = 0;
  switch_domain(ctx, DOMAIN_PAYLOAD);

  undo_padding(ctx, nbytes);

  /* In units of whole words. */
  while (nbytes >= WORD_BYTES)
  {
    body_block_decrypt(ctx, cipher, plain, offset, offset + 1);
    plain += WORD_BYTES;
    cipher += WORD_BYTES;
    nbytes -= WORD_BYTES;
    offset += 1;
  }

  /* And then, finally, bytewise. */
  uint8_t tmp[WORD_BYTES];
  write32_le(ctx->s[offset], tmp);

  for (size_t i = 0; i < nbytes; i++)
  {
    uint8_t c = cipher[i];
    plain[i] = tmp[i] ^ c;
    tmp[i] = c;
  }

  ctx->s[offset] = read32_le(tmp);
}