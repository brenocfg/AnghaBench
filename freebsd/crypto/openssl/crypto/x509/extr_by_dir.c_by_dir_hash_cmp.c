#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ hash; } ;
typedef  TYPE_1__ BY_DIR_HASH ;

/* Variables and functions */

__attribute__((used)) static int by_dir_hash_cmp(const BY_DIR_HASH *const *a,
                           const BY_DIR_HASH *const *b)
{
    if ((*a)->hash > (*b)->hash)
        return 1;
    if ((*a)->hash < (*b)->hash)
        return -1;
    return 0;
}