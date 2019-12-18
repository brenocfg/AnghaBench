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
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  EVBASE_ACQUIRE_LOCK (struct event_base*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EVBASE_RELEASE_LOCK (struct event_base*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dump_active_event_fn ; 
 int /*<<< orphan*/  dump_inserted_event_fn ; 
 int /*<<< orphan*/  event_base_foreach_event_nolock_ (struct event_base*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  th_base_lock ; 

void
event_base_dump_events(struct event_base *base, FILE *output)
{
	EVBASE_ACQUIRE_LOCK(base, th_base_lock);
	fprintf(output, "Inserted events:\n");
	event_base_foreach_event_nolock_(base, dump_inserted_event_fn, output);

	fprintf(output, "Active events:\n");
	event_base_foreach_event_nolock_(base, dump_active_event_fn, output);
	EVBASE_RELEASE_LOCK(base, th_base_lock);
}