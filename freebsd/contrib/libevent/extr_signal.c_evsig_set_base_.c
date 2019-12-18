#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/ * ev_signal_pair; int /*<<< orphan*/  ev_n_signals_added; } ;
struct event_base {TYPE_1__ sig; } ;

/* Variables and functions */
 int /*<<< orphan*/  EVSIGBASE_LOCK () ; 
 int /*<<< orphan*/  EVSIGBASE_UNLOCK () ; 
 struct event_base* evsig_base ; 
 int /*<<< orphan*/  evsig_base_fd ; 
 int /*<<< orphan*/  evsig_base_n_signals_added ; 

void
evsig_set_base_(struct event_base *base)
{
	EVSIGBASE_LOCK();
	evsig_base = base;
	evsig_base_n_signals_added = base->sig.ev_n_signals_added;
	evsig_base_fd = base->sig.ev_signal_pair[1];
	EVSIGBASE_UNLOCK();
}