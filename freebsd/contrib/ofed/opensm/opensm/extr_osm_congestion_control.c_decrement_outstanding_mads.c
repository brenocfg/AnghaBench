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
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_3__ {int /*<<< orphan*/  sig_mads_on_wire_continue; int /*<<< orphan*/  outstanding_mads_on_wire; int /*<<< orphan*/  outstanding_mads_done_event; int /*<<< orphan*/  outstanding_mads; } ;
typedef  TYPE_1__ osm_congestion_control_t ;

/* Variables and functions */
 int /*<<< orphan*/  cl_atomic_dec (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cl_event_signal (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline void decrement_outstanding_mads(osm_congestion_control_t *p_cc)
{
	uint32_t outstanding;

	outstanding = cl_atomic_dec(&p_cc->outstanding_mads);
	if (!outstanding)
		cl_event_signal(&p_cc->outstanding_mads_done_event);

	cl_atomic_dec(&p_cc->outstanding_mads_on_wire);
	cl_event_signal(&p_cc->sig_mads_on_wire_continue);
}