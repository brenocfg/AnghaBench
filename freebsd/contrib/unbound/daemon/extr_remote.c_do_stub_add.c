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
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_2__ {scalar_t__ anchors; int /*<<< orphan*/  hints; struct iter_forwards* fwds; } ;
struct worker {TYPE_1__ env; } ;
struct iter_forwards {int dummy; } ;
struct delegpt {int dummy; } ;
typedef  int /*<<< orphan*/  RES ;

/* Variables and functions */
 int /*<<< orphan*/  LDNS_RR_CLASS_IN ; 
 int /*<<< orphan*/  anchors_add_insecure (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  anchors_delete_insecure (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  delegpt_free_mlc (struct delegpt*) ; 
 int /*<<< orphan*/  forwards_add_stub_hole (struct iter_forwards*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  forwards_delete_stub_hole (struct iter_forwards*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hints_add_stub (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct delegpt*,int) ; 
 int /*<<< orphan*/  parse_fs_args (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ **,struct delegpt**,int*,int*) ; 
 int /*<<< orphan*/  send_ok (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ssl_printf (int /*<<< orphan*/ *,char*) ; 

__attribute__((used)) static void
do_stub_add(RES* ssl, struct worker* worker, char* args)
{
	struct iter_forwards* fwd = worker->env.fwds;
	int insecure = 0, prime = 0;
	uint8_t* nm = NULL;
	struct delegpt* dp = NULL;
	if(!parse_fs_args(ssl, args, &nm, &dp, &insecure, &prime))
		return;
	if(insecure && worker->env.anchors) {
		if(!anchors_add_insecure(worker->env.anchors, LDNS_RR_CLASS_IN,
			nm)) {
			(void)ssl_printf(ssl, "error out of memory\n");
			delegpt_free_mlc(dp);
			free(nm);
			return;
		}
	}
	if(!forwards_add_stub_hole(fwd, LDNS_RR_CLASS_IN, nm)) {
		if(insecure && worker->env.anchors)
			anchors_delete_insecure(worker->env.anchors,
				LDNS_RR_CLASS_IN, nm);
		(void)ssl_printf(ssl, "error out of memory\n");
		delegpt_free_mlc(dp);
		free(nm);
		return;
	}
	if(!hints_add_stub(worker->env.hints, LDNS_RR_CLASS_IN, dp, !prime)) {
		(void)ssl_printf(ssl, "error out of memory\n");
		forwards_delete_stub_hole(fwd, LDNS_RR_CLASS_IN, nm);
		if(insecure && worker->env.anchors)
			anchors_delete_insecure(worker->env.anchors,
				LDNS_RR_CLASS_IN, nm);
		free(nm);
		return;
	}
	free(nm);
	send_ok(ssl);
}