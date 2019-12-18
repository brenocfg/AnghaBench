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
struct kinfo_kstack {int kkst_tid; } ;

/* Variables and functions */

__attribute__((used)) static int
kinfo_kstack_compare(const void *a, const void *b)
{

        return ((const struct kinfo_kstack *)a)->kkst_tid -
            ((const struct kinfo_kstack *)b)->kkst_tid;
}