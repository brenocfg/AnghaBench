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
struct module_qstate {int /*<<< orphan*/  return_rcode; int /*<<< orphan*/ * ext_state; } ;

/* Variables and functions */
 int /*<<< orphan*/  LDNS_RCODE_SERVFAIL ; 
 int /*<<< orphan*/  module_error ; 

__attribute__((used)) static int
val_error(struct module_qstate* qstate, int id)
{
	qstate->ext_state[id] = module_error;
	qstate->return_rcode = LDNS_RCODE_SERVFAIL;
	return 0;
}