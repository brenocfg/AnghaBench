#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ib_portid_t ;
struct TYPE_6__ {int /*<<< orphan*/  change_flgs; } ;
struct TYPE_7__ {TYPE_1__ ntc_144; } ;
struct TYPE_8__ {TYPE_2__ data_details; } ;
typedef  TYPE_3__ ib_mad_notice_attr_t ;

/* Variables and functions */
 int /*<<< orphan*/  TRAP_144_MASK_NODE_DESCRIPTION_CHANGE ; 
 int /*<<< orphan*/  build_trap144_local (TYPE_3__*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void build_trap144_nodedesc(ib_mad_notice_attr_t * n, ib_portid_t * port)
{
	build_trap144_local(n, port);
	n->data_details.ntc_144.change_flgs =
	    TRAP_144_MASK_NODE_DESCRIPTION_CHANGE;
}