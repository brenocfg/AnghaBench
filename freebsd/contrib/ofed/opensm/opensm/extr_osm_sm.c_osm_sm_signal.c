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
struct TYPE_3__ {int signal_mask; int /*<<< orphan*/  signal_lock; int /*<<< orphan*/  signal_event; } ;
typedef  TYPE_1__ osm_sm_t ;
typedef  int osm_signal_t ;

/* Variables and functions */
 int /*<<< orphan*/  cl_event_signal (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cl_spinlock_acquire (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cl_spinlock_release (int /*<<< orphan*/ *) ; 

void osm_sm_signal(osm_sm_t * p_sm, osm_signal_t signal)
{
	cl_spinlock_acquire(&p_sm->signal_lock);
	p_sm->signal_mask |= 1 << signal;
	cl_event_signal(&p_sm->signal_event);
	cl_spinlock_release(&p_sm->signal_lock);
}