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
typedef  int uint8_t ;
typedef  int uint32_t ;
typedef  int /*<<< orphan*/  cf_poly1305 ;

/* Variables and functions */
 int /*<<< orphan*/  poly1305_block (int /*<<< orphan*/ *,int*) ; 

__attribute__((used)) static void poly1305_whole_block(void *vctx,
                                 const uint8_t *buf)
{
  cf_poly1305 *ctx = vctx;
  uint32_t c[17];
  int i;

  for (i = 0; i < 16; i++)
    c[i] = buf[i];

  c[16] = 1;
  poly1305_block(ctx, c);
}