#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_3__ {int /*<<< orphan*/ * s; } ;
typedef  TYPE_1__ norx32_ctx ;
struct TYPE_4__ {TYPE_1__* ctx; } ;
typedef  TYPE_2__ blockctx ;

/* Variables and functions */
 int RATE_WORDS ; 
 int /*<<< orphan*/  WORD_BYTES ; 
 int /*<<< orphan*/  read32_le (int /*<<< orphan*/  const*) ; 

__attribute__((used)) static void input_block_final(void *vctx, const uint8_t *data)
{
  blockctx *bctx = vctx;
  norx32_ctx *ctx = bctx->ctx;

  /* just xor-in data. */
  for (int i = 0; i < RATE_WORDS; i++)
  {
    ctx->s[i] ^= read32_le(data);
    data += WORD_BYTES;
  }
}