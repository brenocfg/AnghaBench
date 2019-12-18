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
typedef  scalar_t__* longfelem ;
typedef  scalar_t__* felem ;

/* Variables and functions */
 int /*<<< orphan*/  felem_reduce_ (scalar_t__*,scalar_t__* const) ; 
 scalar_t__* zero105 ; 

__attribute__((used)) static void felem_reduce_zero105(felem out, const longfelem in)
{
    out[0] = zero105[0] + in[0];
    out[1] = zero105[1] + in[1];
    out[2] = zero105[2] + in[2];
    out[3] = zero105[3] + in[3];

    felem_reduce_(out, in);

    /*-
     * out[0] > 2^105 - 2^41 - 2^9 - 2^71 - 2^103 - 2^71 - 2^103 > 0
     * out[1] > 2^105 - 2^71 - 2^103 > 0
     * out[2] > 2^105 - 2^41 + 2^9 - 2^71 - 2^103 > 0
     * out[3] > 2^105 - 2^41 + 2^9 - 2^71 - 2^103 - 2^103 > 0
     *
     * out[0] < 2^105 + 2^71 + 2^71 + 2^103 < 2^106
     * out[1] < 2^105 + 2^71 + 2^71 + 2^103 < 2^106
     * out[2] < 2^105 + 2^71 + 2^71 + 2^71 + 2^103 < 2^106
     * out[3] < 2^105 + 2^71 + 2^103 + 2^71 < 2^106
     */
}