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
struct module_qstate {int dummy; } ;
struct iter_qstate {int /*<<< orphan*/  final_state; int /*<<< orphan*/  state; } ;
struct iter_env {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  FINISHED_STATE ; 
 int /*<<< orphan*/  INIT_REQUEST_STATE ; 
 int /*<<< orphan*/  VERB_ALGO ; 
 int /*<<< orphan*/  iter_handle (struct module_qstate*,struct iter_qstate*,struct iter_env*,int) ; 
 int /*<<< orphan*/  verbose (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void
process_request(struct module_qstate* qstate, struct iter_qstate* iq,
	struct iter_env* ie, int id)
{
	/* external requests start in the INIT state, and finish using the
	 * FINISHED state. */
	iq->state = INIT_REQUEST_STATE;
	iq->final_state = FINISHED_STATE;
	verbose(VERB_ALGO, "process_request: new external request event");
	iter_handle(qstate, iq, ie, id);
}