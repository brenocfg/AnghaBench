#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {TYPE_1__* ranges; } ;
struct TYPE_8__ {scalar_t__ final_size; TYPE_2__ acked; } ;
typedef  TYPE_3__ quicly_sendstate_t ;
struct TYPE_6__ {int end; } ;

/* Variables and functions */
 int /*<<< orphan*/  quicly_sendstate_init (TYPE_3__*) ; 

void quicly_sendstate_init_closed(quicly_sendstate_t *state)
{
    quicly_sendstate_init(state);
    state->acked.ranges[0].end = 1;
    state->final_size = 0;
}