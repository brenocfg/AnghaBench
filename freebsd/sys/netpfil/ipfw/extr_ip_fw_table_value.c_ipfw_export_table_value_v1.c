#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct table_value {int /*<<< orphan*/  zoneid; int /*<<< orphan*/  nh6; int /*<<< orphan*/  nh4; int /*<<< orphan*/  limit; int /*<<< orphan*/  dscp; int /*<<< orphan*/  nat; int /*<<< orphan*/  fib; int /*<<< orphan*/  netgraph; int /*<<< orphan*/  skipto; int /*<<< orphan*/  divert; int /*<<< orphan*/  pipe; int /*<<< orphan*/  tag; } ;
typedef  int /*<<< orphan*/  iv ;
struct TYPE_6__ {int /*<<< orphan*/  zoneid; int /*<<< orphan*/  nh6; int /*<<< orphan*/  nh4; int /*<<< orphan*/  limit; int /*<<< orphan*/  dscp; int /*<<< orphan*/  nat; int /*<<< orphan*/  fib; int /*<<< orphan*/  netgraph; int /*<<< orphan*/  skipto; int /*<<< orphan*/  divert; int /*<<< orphan*/  pipe; int /*<<< orphan*/  tag; } ;
typedef  TYPE_1__ ipfw_table_value ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (TYPE_1__*,TYPE_1__*,int) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 

void
ipfw_export_table_value_v1(struct table_value *v, ipfw_table_value *piv)
{
	ipfw_table_value iv;

	memset(&iv, 0, sizeof(iv));
	iv.tag = v->tag;
	iv.pipe = v->pipe;
	iv.divert = v->divert;
	iv.skipto = v->skipto;
	iv.netgraph = v->netgraph;
	iv.fib = v->fib;
	iv.nat = v->nat;
	iv.dscp = v->dscp;
	iv.limit = v->limit;
	iv.nh4 = v->nh4;
	iv.nh6 = v->nh6;
	iv.zoneid = v->zoneid;

	memcpy(piv, &iv, sizeof(iv));
}