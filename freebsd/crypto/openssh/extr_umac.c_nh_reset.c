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
struct TYPE_3__ {scalar_t__* state; scalar_t__ next_data_empty; scalar_t__ bytes_hashed; } ;
typedef  TYPE_1__ nh_ctx ;

/* Variables and functions */

__attribute__((used)) static void nh_reset(nh_ctx *hc)
/* Reset nh_ctx to ready for hashing of new data */
{
    hc->bytes_hashed = 0;
    hc->next_data_empty = 0;
    hc->state[0] = 0;
#if (UMAC_OUTPUT_LEN >= 8)
    hc->state[1] = 0;
#endif
#if (UMAC_OUTPUT_LEN >= 12)
    hc->state[2] = 0;
#endif
#if (UMAC_OUTPUT_LEN == 16)
    hc->state[3] = 0;
#endif

}