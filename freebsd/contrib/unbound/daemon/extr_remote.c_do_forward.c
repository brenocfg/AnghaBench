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
struct TYPE_2__ {int /*<<< orphan*/  mesh; struct iter_forwards* fwds; } ;
struct worker {TYPE_1__ env; } ;
struct iter_forwards {int dummy; } ;
struct delegpt {int dummy; } ;
typedef  int /*<<< orphan*/  RES ;

/* Variables and functions */
 int /*<<< orphan*/  LDNS_RR_CLASS_IN ; 
 int /*<<< orphan*/  forwards_add_zone (struct iter_forwards*,int /*<<< orphan*/ ,struct delegpt*) ; 
 int /*<<< orphan*/  forwards_delete_zone (struct iter_forwards*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mesh_delete_all (int /*<<< orphan*/ ) ; 
 struct delegpt* parse_delegpt (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  print_root_fwds (int /*<<< orphan*/ *,struct iter_forwards*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  send_ok (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ssl_printf (int /*<<< orphan*/ *,char*) ; 
 scalar_t__ strcmp (char*,char*) ; 

__attribute__((used)) static void
do_forward(RES* ssl, struct worker* worker, char* args)
{
	struct iter_forwards* fwd = worker->env.fwds;
	uint8_t* root = (uint8_t*)"\000";
	if(!fwd) {
		(void)ssl_printf(ssl, "error: structure not allocated\n");
		return;
	}
	if(args == NULL || args[0] == 0) {
		(void)print_root_fwds(ssl, fwd, root);
		return;
	}
	/* set root forwards for this thread. since we are in remote control
	 * the actual mesh is not running, so we can freely edit it. */
	/* delete all the existing queries first */
	mesh_delete_all(worker->env.mesh);
	if(strcmp(args, "off") == 0) {
		forwards_delete_zone(fwd, LDNS_RR_CLASS_IN, root);
	} else {
		struct delegpt* dp;
		if(!(dp = parse_delegpt(ssl, args, root, 0)))
			return;
		if(!forwards_add_zone(fwd, LDNS_RR_CLASS_IN, dp)) {
			(void)ssl_printf(ssl, "error out of memory\n");
			return;
		}
	}
	send_ok(ssl);
}