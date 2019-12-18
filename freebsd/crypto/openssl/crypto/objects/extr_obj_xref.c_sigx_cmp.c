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
struct TYPE_4__ {int hash_id; int pkey_id; } ;
typedef  TYPE_1__ nid_triple ;

/* Variables and functions */

__attribute__((used)) static int sigx_cmp(const nid_triple *const *a, const nid_triple *const *b)
{
    int ret;
    ret = (*a)->hash_id - (*b)->hash_id;
    if (ret)
        return ret;
    return (*a)->pkey_id - (*b)->pkey_id;
}