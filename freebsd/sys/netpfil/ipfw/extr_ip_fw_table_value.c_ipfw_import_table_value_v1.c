#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  v ;
struct table_value {int /*<<< orphan*/  zoneid; int /*<<< orphan*/  limit; int /*<<< orphan*/  nh6; int /*<<< orphan*/  nh4; int /*<<< orphan*/  dscp; int /*<<< orphan*/  nat; int /*<<< orphan*/  fib; int /*<<< orphan*/  netgraph; int /*<<< orphan*/  skipto; int /*<<< orphan*/  divert; int /*<<< orphan*/  pipe; int /*<<< orphan*/  tag; } ;
struct TYPE_4__ {int /*<<< orphan*/  zoneid; int /*<<< orphan*/  limit; int /*<<< orphan*/  nh6; int /*<<< orphan*/  nh4; int /*<<< orphan*/  dscp; int /*<<< orphan*/  nat; int /*<<< orphan*/  fib; int /*<<< orphan*/  netgraph; int /*<<< orphan*/  skipto; int /*<<< orphan*/  divert; int /*<<< orphan*/  pipe; int /*<<< orphan*/  tag; } ;
typedef  TYPE_1__ ipfw_table_value ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (TYPE_1__*,struct table_value*,int) ; 
 int /*<<< orphan*/  memset (struct table_value*,int /*<<< orphan*/ ,int) ; 

void
ipfw_import_table_value_v1(ipfw_table_value *iv)
{
	struct table_value v;

	memset(&v, 0, sizeof(v));
	v.tag = iv->tag;
	v.pipe = iv->pipe;
	v.divert = iv->divert;
	v.skipto = iv->skipto;
	v.netgraph = iv->netgraph;
	v.fib = iv->fib;
	v.nat = iv->nat;
	v.dscp = iv->dscp;
	v.nh4 = iv->nh4;
	v.nh6 = iv->nh6;
	v.limit = iv->limit;
	v.zoneid = iv->zoneid;

	memcpy(iv, &v, sizeof(ipfw_table_value));
}