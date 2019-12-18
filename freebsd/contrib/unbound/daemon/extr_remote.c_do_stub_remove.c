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
struct TYPE_2__ {int /*<<< orphan*/  hints; scalar_t__ anchors; struct iter_forwards* fwds; } ;
struct worker {TYPE_1__ env; } ;
struct iter_forwards {int dummy; } ;
typedef  int /*<<< orphan*/  RES ;

/* Variables and functions */
 int /*<<< orphan*/  LDNS_RR_CLASS_IN ; 
 int /*<<< orphan*/  anchors_delete_insecure (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  forwards_delete_stub_hole (struct iter_forwards*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hints_delete_stub (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  parse_fs_args (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ **,int /*<<< orphan*/ *,int*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  send_ok (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
do_stub_remove(RES* ssl, struct worker* worker, char* args)
{
	struct iter_forwards* fwd = worker->env.fwds;
	int insecure = 0;
	uint8_t* nm = NULL;
	if(!parse_fs_args(ssl, args, &nm, NULL, &insecure, NULL))
		return;
	if(insecure && worker->env.anchors)
		anchors_delete_insecure(worker->env.anchors, LDNS_RR_CLASS_IN,
			nm);
	forwards_delete_stub_hole(fwd, LDNS_RR_CLASS_IN, nm);
	hints_delete_stub(worker->env.hints, LDNS_RR_CLASS_IN, nm);
	free(nm);
	send_ok(ssl);
}