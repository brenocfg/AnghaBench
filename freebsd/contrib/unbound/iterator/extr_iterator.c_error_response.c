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
struct module_qstate {int return_rcode; int /*<<< orphan*/ * ext_state; int /*<<< orphan*/ * return_msg; } ;
struct TYPE_2__ {char* name; } ;

/* Variables and functions */
 int /*<<< orphan*/  VERB_QUERY ; 
 int /*<<< orphan*/  module_finished ; 
 TYPE_1__* sldns_lookup_by_id (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  sldns_rcodes ; 
 int /*<<< orphan*/  verbose (int /*<<< orphan*/ ,char*,char*) ; 

__attribute__((used)) static int
error_response(struct module_qstate* qstate, int id, int rcode)
{
	verbose(VERB_QUERY, "return error response %s", 
		sldns_lookup_by_id(sldns_rcodes, rcode)?
		sldns_lookup_by_id(sldns_rcodes, rcode)->name:"??");
	qstate->return_rcode = rcode;
	qstate->return_msg = NULL;
	qstate->ext_state[id] = module_finished;
	return 0;
}