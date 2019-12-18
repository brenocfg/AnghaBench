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
struct TYPE_2__ {scalar_t__ anchors; struct iter_forwards* fwds; } ;
struct worker {TYPE_1__ env; } ;
struct iter_forwards {int dummy; } ;
struct delegpt {int dummy; } ;
typedef  int /*<<< orphan*/  RES ;

/* Variables and functions */
 int /*<<< orphan*/  LDNS_RR_CLASS_IN ; 
 int /*<<< orphan*/  anchors_add_insecure (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  delegpt_free_mlc (struct delegpt*) ; 
 int /*<<< orphan*/  forwards_add_zone (struct iter_forwards*,int /*<<< orphan*/ ,struct delegpt*) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  parse_fs_args (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ **,struct delegpt**,int*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  send_ok (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ssl_printf (int /*<<< orphan*/ *,char*) ; 

__attribute__((used)) static void
do_forward_add(RES* ssl, struct worker* worker, char* args)
{
	struct iter_forwards* fwd = worker->env.fwds;
	int insecure = 0;
	uint8_t* nm = NULL;
	struct delegpt* dp = NULL;
	if(!parse_fs_args(ssl, args, &nm, &dp, &insecure, NULL))
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
	if(!forwards_add_zone(fwd, LDNS_RR_CLASS_IN, dp)) {
		(void)ssl_printf(ssl, "error out of memory\n");
		free(nm);
		return;
	}
	free(nm);
	send_ok(ssl);
}