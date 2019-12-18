#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct event_base {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  evmap_io_delete_all_iter_fn ; 
 int /*<<< orphan*/  evmap_io_foreach_fd (struct event_base*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  evmap_signal_delete_all_iter_fn ; 
 int /*<<< orphan*/  evmap_signal_foreach_signal (struct event_base*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void
evmap_delete_all_(struct event_base *base)
{
	evmap_signal_foreach_signal(base, evmap_signal_delete_all_iter_fn, NULL);
	evmap_io_foreach_fd(base, evmap_io_delete_all_iter_fn, NULL);
}