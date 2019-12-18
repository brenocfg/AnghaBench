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
struct query_state {int /*<<< orphan*/  (* destroy_func ) (struct query_state*) ;struct query_state* io_buffer; struct query_state* eid_str; } ;

/* Variables and functions */
 int /*<<< orphan*/  TRACE_IN (void (*) (struct query_state*)) ; 
 int /*<<< orphan*/  TRACE_OUT (void (*) (struct query_state*)) ; 
 int /*<<< orphan*/  free (struct query_state*) ; 
 int /*<<< orphan*/  stub1 (struct query_state*) ; 

void
destroy_query_state(struct query_state *qstate)
{

	TRACE_IN(destroy_query_state);
	if (qstate->eid_str != NULL)
	    free(qstate->eid_str);

	if (qstate->io_buffer != NULL)
		free(qstate->io_buffer);

	qstate->destroy_func(qstate);
	free(qstate);
	TRACE_OUT(destroy_query_state);
}