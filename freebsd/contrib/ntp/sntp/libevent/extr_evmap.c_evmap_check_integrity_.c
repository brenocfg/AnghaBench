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
struct event_base {TYPE_1__* evsel; } ;
struct TYPE_2__ {scalar_t__ add; } ;

/* Variables and functions */
 scalar_t__ event_changelist_add_ ; 
 int /*<<< orphan*/  event_changelist_assert_ok (struct event_base*) ; 
 int /*<<< orphan*/  evmap_io_check_integrity_fn ; 
 int /*<<< orphan*/  evmap_io_foreach_fd (struct event_base*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  evmap_signal_check_integrity_fn ; 
 int /*<<< orphan*/  evmap_signal_foreach_signal (struct event_base*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void
evmap_check_integrity_(struct event_base *base)
{
	evmap_io_foreach_fd(base, evmap_io_check_integrity_fn, NULL);
	evmap_signal_foreach_signal(base, evmap_signal_check_integrity_fn, NULL);

	if (base->evsel->add == event_changelist_add_)
		event_changelist_assert_ok(base);
}