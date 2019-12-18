#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {TYPE_1__* track; } ;
typedef  TYPE_2__ serf_bucket_alloc_t ;
struct TYPE_4__ {scalar_t__ next_index; scalar_t__ num_used; } ;

/* Variables and functions */

void serf_debug__closed_conn(serf_bucket_alloc_t *allocator)
{
#ifdef SERF_DEBUG_BUCKET_USE

    /* Just reset the number used so that we don't examine the info[] */
    allocator->track->num_used = 0;
    allocator->track->next_index = 0;

#endif
}