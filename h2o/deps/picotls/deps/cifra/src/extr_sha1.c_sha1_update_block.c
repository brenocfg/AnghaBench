#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int uint32_t ;
struct TYPE_2__ {int* H; int /*<<< orphan*/  blocks; } ;
typedef  TYPE_1__ cf_sha1_context ;

/* Variables and functions */
 int read32_be (int /*<<< orphan*/  const*) ; 
 int rotl32 (int,int) ; 

__attribute__((used)) static void sha1_update_block(void *vctx, const uint8_t *inp)
{
  cf_sha1_context *ctx = vctx;

  /* This is a 16-word window into the whole W array. */
  uint32_t W[16];

  uint32_t a = ctx->H[0],
           b = ctx->H[1],
           c = ctx->H[2],
           d = ctx->H[3],
           e = ctx->H[4],
           Wt;

  for (size_t t = 0; t < 80; t++)
  {
    /* For W[0..16] we process the input into W.
     * For W[16..79] we compute the next W value:
     *
     * W[t] = (W[t - 3] ^ W[t - 8] ^ W[t - 14] ^ W[t - 16]) <<< 1
     *
     * But all W indices are reduced mod 16 into our window.
     */
    if (t < 16)
    {
      W[t] = Wt = read32_be(inp);
      inp += 4;
    } else {
      Wt = W[(t - 3) % 16] ^ W[(t - 8) % 16] ^ W[(t - 14) % 16] ^ W[(t - 16) % 16];
      Wt = rotl32(Wt, 1);
      W[t % 16] = Wt;
    }

    uint32_t f, k;

    if (t <= 19)
    {
      f = (b & c) | (~b & d);
      k = 0x5a827999;
    } else if (t <= 39) {
      f = b ^ c ^ d;
      k = 0x6ed9eba1;
    } else if (t <= 59) {
      f = (b & c) | (b & d) | (c & d);
      k = 0x8f1bbcdc;
    } else {
      f = b ^ c ^ d;
      k = 0xca62c1d6;
    }

    uint32_t temp = rotl32(a, 5) + f + e + k + Wt;
    e = d;
    d = c;
    c = rotl32(b, 30);
    b = a;
    a = temp;
  }

  ctx->H[0] += a;
  ctx->H[1] += b;
  ctx->H[2] += c;
  ctx->H[3] += d;
  ctx->H[4] += e;

  ctx->blocks++;
}