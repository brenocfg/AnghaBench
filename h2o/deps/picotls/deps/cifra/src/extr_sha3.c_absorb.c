#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int uint16_t ;
struct TYPE_7__ {TYPE_1__** A; } ;
typedef  TYPE_2__ cf_sha3_context ;
struct TYPE_8__ {int /*<<< orphan*/  evn; int /*<<< orphan*/  odd; } ;
typedef  TYPE_3__ cf_sha3_bi ;
struct TYPE_6__ {int /*<<< orphan*/  evn; int /*<<< orphan*/  odd; } ;

/* Variables and functions */
 int /*<<< orphan*/  read64_bi (TYPE_3__*,int /*<<< orphan*/  const*) ; 

__attribute__((used)) static void absorb(cf_sha3_context *ctx, const uint8_t *data, uint16_t sz)
{
  uint16_t lanes = sz / 8;

  for (uint16_t x = 0, y = 0, i = 0; i < lanes; i++)
  {
    cf_sha3_bi bi;
    read64_bi(&bi, data);
    ctx->A[x][y].odd ^= bi.odd;
    ctx->A[x][y].evn ^= bi.evn;
    data += 8;

    x++;
    if (x == 5)
    {
      y++;
      x = 0;
    }
  }
}