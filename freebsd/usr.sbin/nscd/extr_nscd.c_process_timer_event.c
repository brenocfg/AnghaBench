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
struct runtime_env {int dummy; } ;
struct query_state {int dummy; } ;
struct kevent {int /*<<< orphan*/  ident; scalar_t__ udata; } ;
struct configuration {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  TRACE_IN (void (*) (struct kevent*,struct runtime_env*,struct configuration*)) ; 
 int /*<<< orphan*/  TRACE_OUT (void (*) (struct kevent*,struct runtime_env*,struct configuration*)) ; 
 int /*<<< orphan*/  close (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  destroy_query_state (struct query_state*) ; 

__attribute__((used)) static void
process_timer_event(struct kevent *event_data, struct runtime_env *env,
	struct configuration *config)
{
	struct query_state	*qstate;

	TRACE_IN(process_timer_event);
	qstate = (struct query_state *)event_data->udata;
	destroy_query_state(qstate);
	close(event_data->ident);
	TRACE_OUT(process_timer_event);
}