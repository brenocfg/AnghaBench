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
struct TYPE_4__ {int pbe_type; int pbe_nid; } ;
typedef  TYPE_1__ EVP_PBE_CTL ;

/* Variables and functions */

__attribute__((used)) static int pbe_cmp(const EVP_PBE_CTL *const *a, const EVP_PBE_CTL *const *b)
{
    int ret = (*a)->pbe_type - (*b)->pbe_type;
    if (ret)
        return ret;
    else
        return (*a)->pbe_nid - (*b)->pbe_nid;
}