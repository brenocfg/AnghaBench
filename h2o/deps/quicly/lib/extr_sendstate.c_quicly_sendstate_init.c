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
struct TYPE_3__ {int /*<<< orphan*/  final_size; scalar_t__ size_inflight; int /*<<< orphan*/  pending; int /*<<< orphan*/  acked; } ;
typedef  TYPE_1__ quicly_sendstate_t ;

/* Variables and functions */
 int /*<<< orphan*/  UINT64_MAX ; 
 int /*<<< orphan*/  quicly_ranges_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  quicly_ranges_init_with_range (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void quicly_sendstate_init(quicly_sendstate_t *state)
{
    quicly_ranges_init_with_range(&state->acked, 0, 0);
    quicly_ranges_init(&state->pending);
    state->size_inflight = 0;
    state->final_size = UINT64_MAX;
}