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
struct TYPE_3__ {scalar_t__ num_alloc; } ;
typedef  TYPE_1__ serf_bucket_alloc_t ;

/* Variables and functions */
 int /*<<< orphan*/  abort () ; 

void serf_debug__bucket_alloc_check(
    serf_bucket_alloc_t *allocator)
{
#ifdef SERF_DEBUG_BUCKET_USE
    if (allocator->num_alloc != 0) {
        abort();
    }
#endif
}