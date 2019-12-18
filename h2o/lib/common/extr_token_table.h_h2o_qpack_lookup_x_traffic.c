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
typedef  int int32_t ;
typedef  int /*<<< orphan*/  h2o_iovec_t ;

/* Variables and functions */

int32_t h2o_qpack_lookup_x_traffic(h2o_iovec_t value, int *is_exact)
{
    *is_exact = 0;
    return -1;
}