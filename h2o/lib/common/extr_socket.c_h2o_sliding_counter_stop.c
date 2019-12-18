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
typedef  scalar_t__ uint64_t ;
struct TYPE_6__ {int sum; size_t index; scalar_t__* slots; } ;
struct TYPE_5__ {scalar_t__ start_at; } ;
struct TYPE_7__ {int average; TYPE_2__ prev; TYPE_1__ cur; } ;
typedef  TYPE_3__ h2o_sliding_counter_t ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 

void h2o_sliding_counter_stop(h2o_sliding_counter_t *counter, uint64_t now)
{
    uint64_t elapsed;

    assert(counter->cur.start_at != 0);

    /* calculate the time used, and reset cur */
    if (now <= counter->cur.start_at)
        elapsed = 0;
    else
        elapsed = now - counter->cur.start_at;
    counter->cur.start_at = 0;

    /* adjust prev */
    counter->prev.sum += elapsed;
    counter->prev.sum -= counter->prev.slots[counter->prev.index];
    counter->prev.slots[counter->prev.index] = elapsed;
    if (++counter->prev.index >= sizeof(counter->prev.slots) / sizeof(counter->prev.slots[0]))
        counter->prev.index = 0;

    /* recalc average */
    counter->average = counter->prev.sum / (sizeof(counter->prev.slots) / sizeof(counter->prev.slots[0]));
}