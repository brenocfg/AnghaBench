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
struct query_state {int /*<<< orphan*/  request; int /*<<< orphan*/  response; } ;

/* Variables and functions */
 int /*<<< orphan*/  TRACE_IN (void (*) (struct query_state*)) ; 
 int /*<<< orphan*/  TRACE_OUT (void (*) (struct query_state*)) ; 
 int /*<<< orphan*/  finalize_comm_element (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
on_query_destroy(struct query_state *qstate)
{

	TRACE_IN(on_query_destroy);
	finalize_comm_element(&qstate->response);
	finalize_comm_element(&qstate->request);
	TRACE_OUT(on_query_destroy);
}