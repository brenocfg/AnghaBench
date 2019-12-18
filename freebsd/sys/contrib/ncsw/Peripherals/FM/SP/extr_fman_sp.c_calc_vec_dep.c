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
typedef  int uint32_t ;
struct fman_ext_pools {int num_pools_used; TYPE_1__* ext_buf_pool; } ;
struct TYPE_2__ {int id; } ;

/* Variables and functions */

__attribute__((used)) static inline uint32_t calc_vec_dep(int max_pools, bool *pools,
        struct fman_ext_pools *ext_buf_pools, uint32_t mask)
{
    int i, j;
    uint32_t vector = 0;
    for (i = 0; i < max_pools; i++)
        if (pools[i])
            for (j = 0; j < ext_buf_pools->num_pools_used; j++)
                if (i == ext_buf_pools->ext_buf_pool[j].id) {
                    vector |= mask >> j;
                    break;
                }
    return vector;
}