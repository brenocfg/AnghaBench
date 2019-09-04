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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  scalar_t__ uint16_t ;
struct TYPE_3__ {int /*<<< orphan*/ ** A; } ;
typedef  TYPE_1__ cf_sha3_context ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  write64_bi (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void extract(cf_sha3_context *ctx, uint8_t *out, size_t nbytes)
{
  uint16_t lanes = (nbytes + 7) / 8;

  for (uint16_t x = 0, y = 0, i = 0; i < lanes; i++)
  {
    if (nbytes >= 8)
    {
      write64_bi(&ctx->A[x][y], out);
      out += 8;
      nbytes -= 8;
    } else {
      uint8_t buf[8];
      write64_bi(&ctx->A[x][y], buf);
      memcpy(out, buf, nbytes);
      out += nbytes;
      nbytes = 0;
    }
    
    x++;
    if (x == 5)
    {
      y++;
      x = 0;
    }
  }
}