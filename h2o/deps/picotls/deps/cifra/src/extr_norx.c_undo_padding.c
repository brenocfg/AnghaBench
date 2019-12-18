#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int* s; } ;
typedef  TYPE_1__ norx32_ctx ;

/* Variables and functions */
 size_t RATE_BYTES ; 
 int RATE_WORDS ; 
 size_t WORD_BYTES ; 
 int /*<<< orphan*/  assert (int) ; 

__attribute__((used)) static void undo_padding(norx32_ctx *ctx, size_t bytes)
{
  assert(bytes < RATE_BYTES);
  ctx->s[bytes / WORD_BYTES] ^= 0x01 << ((bytes % WORD_BYTES) * 8);
  ctx->s[RATE_WORDS - 1] ^= 0x80000000;
}