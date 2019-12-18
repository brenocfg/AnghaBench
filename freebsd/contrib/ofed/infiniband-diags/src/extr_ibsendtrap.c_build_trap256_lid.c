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
struct TYPE_6__ {scalar_t__ dr_trunc_hop; } ;
struct TYPE_7__ {TYPE_1__ ntc_256; } ;
struct TYPE_8__ {TYPE_2__ data_details; } ;
typedef  TYPE_3__ ib_mad_notice_attr_t ;

/* Variables and functions */
 int /*<<< orphan*/  build_trap256_local (TYPE_3__*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void build_trap256_lid(ib_mad_notice_attr_t * n, ib_portid_t * port)
{
	build_trap256_local(n, port);
	n->data_details.ntc_256.dr_trunc_hop = 0;
}