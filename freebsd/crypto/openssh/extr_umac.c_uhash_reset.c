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
typedef  TYPE_1__* uhash_ctx_t ;
struct TYPE_3__ {int* poly_accum; scalar_t__ msg_len; int /*<<< orphan*/  hash; } ;

/* Variables and functions */
 int /*<<< orphan*/  nh_reset (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int uhash_reset(uhash_ctx_t pc)
{
    nh_reset(&pc->hash);
    pc->msg_len = 0;
    pc->poly_accum[0] = 1;
#if (UMAC_OUTPUT_LEN >= 8)
    pc->poly_accum[1] = 1;
#endif
#if (UMAC_OUTPUT_LEN >= 12)
    pc->poly_accum[2] = 1;
#endif
#if (UMAC_OUTPUT_LEN == 16)
    pc->poly_accum[3] = 1;
#endif
    return 1;
}