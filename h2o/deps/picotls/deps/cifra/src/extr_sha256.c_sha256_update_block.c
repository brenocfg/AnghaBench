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
typedef  scalar_t__ uint32_t ;
struct TYPE_2__ {int /*<<< orphan*/  blocks; scalar_t__* H; } ;
typedef  TYPE_1__ cf_sha256_context ;

/* Variables and functions */
 scalar_t__ BSIG0 (scalar_t__) ; 
 scalar_t__ BSIG1 (scalar_t__) ; 
 scalar_t__ CH (scalar_t__,scalar_t__,scalar_t__) ; 
 scalar_t__* K ; 
 scalar_t__ MAJ (scalar_t__,scalar_t__,scalar_t__) ; 
 scalar_t__ SSIG0 (scalar_t__) ; 
 scalar_t__ SSIG1 (scalar_t__) ; 
 scalar_t__ read32_be (int /*<<< orphan*/  const*) ; 

__attribute__((used)) static void sha256_update_block(void *vctx, const uint8_t *inp)
{
  cf_sha256_context *ctx = vctx;

  /* This is a 16-word window into the whole W array. */
  uint32_t W[16];

  uint32_t a = ctx->H[0],
           b = ctx->H[1],
           c = ctx->H[2],
           d = ctx->H[3],
           e = ctx->H[4],
           f = ctx->H[5],
           g = ctx->H[6],
           h = ctx->H[7],
           Wt;

  size_t t;
  for (t = 0; t < 64; t++)
  {
    /* For W[0..16] we process the input into W.
     * For W[16..64] we compute the next W value:
     *
     * W[t] = SSIG1(W[t - 2]) + W[t - 7] + SSIG0(W[t - 15]) + W[t - 16];
     *
     * But all W indices are reduced mod 16 into our window.
     */
    if (t < 16)
    {
      W[t] = Wt = read32_be(inp);
      inp += 4;
    } else {
      Wt = SSIG1(W[(t - 2) % 16]) +
           W[(t - 7) % 16] +
           SSIG0(W[(t - 15) % 16]) +
           W[(t - 16) % 16];
      W[t % 16] = Wt;
    }

    uint32_t T1 = h + BSIG1(e) + CH(e, f, g) + K[t] + Wt;
    uint32_t T2 = BSIG0(a) + MAJ(a, b, c);
    h = g;
    g = f;
    f = e;
    e = d + T1;
    d = c;
    c = b;
    b = a;
    a = T1 + T2;
  }

  ctx->H[0] += a;
  ctx->H[1] += b;
  ctx->H[2] += c;
  ctx->H[3] += d;
  ctx->H[4] += e;
  ctx->H[5] += f;
  ctx->H[6] += g;
  ctx->H[7] += h;

  ctx->blocks++;
}