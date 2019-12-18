#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ next_index; scalar_t__ num_used; TYPE_3__* info; } ;
typedef  TYPE_1__ track_state_t ;
struct TYPE_6__ {TYPE_1__* track; } ;
typedef  TYPE_2__ serf_bucket_alloc_t ;
struct TYPE_7__ {scalar_t__ last; } ;
typedef  TYPE_3__ read_status_t ;

/* Variables and functions */
 scalar_t__ APR_SUCCESS ; 
 int /*<<< orphan*/  abort () ; 

void serf_debug__entered_loop(serf_bucket_alloc_t *allocator)
{
#ifdef SERF_DEBUG_BUCKET_USE

    track_state_t *track = allocator->track;
    read_status_t *rs = &track->info[0];

    for ( ; track->num_used; --track->num_used, ++rs ) {
        if (rs->last == APR_SUCCESS) {
            /* Somebody should have read this bucket again. */
            abort();
        }

        /* ### other status values? */
    }

    /* num_used was reset. also need to reset the next index. */
    track->next_index = 0;

#endif
}