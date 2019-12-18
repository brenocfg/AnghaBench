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
struct TYPE_3__ {int /*<<< orphan*/  eos; scalar_t__ data_off; int /*<<< orphan*/  received; } ;
typedef  TYPE_1__ quicly_recvstate_t ;

/* Variables and functions */
 int /*<<< orphan*/  UINT64_MAX ; 
 int /*<<< orphan*/  quicly_ranges_init_with_range (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void quicly_recvstate_init(quicly_recvstate_t *state)
{
    quicly_ranges_init_with_range(&state->received, 0, 0);
    state->data_off = 0;
    state->eos = UINT64_MAX;
}