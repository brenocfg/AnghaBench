#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct table_value {int dummy; } ;
struct table_config {int /*<<< orphan*/  astate; struct table_algo* ta; } ;
struct table_algo {int (* dump_tentry ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*,TYPE_5__*) ;} ;
struct TYPE_8__ {int /*<<< orphan*/  kidx; } ;
struct TYPE_6__ {int /*<<< orphan*/  s_addr; } ;
struct TYPE_7__ {TYPE_1__ addr; } ;
struct TYPE_10__ {TYPE_3__ v; int /*<<< orphan*/  masklen; TYPE_2__ k; } ;
struct dump_args {scalar_t__ cnt; scalar_t__ size; TYPE_5__ tent; struct table_config* tc; int /*<<< orphan*/  ch; int /*<<< orphan*/  ti; int /*<<< orphan*/  uidx; int /*<<< orphan*/  ent; } ;
struct TYPE_9__ {int /*<<< orphan*/  value; int /*<<< orphan*/  masklen; int /*<<< orphan*/  addr; int /*<<< orphan*/  tbl; } ;
typedef  TYPE_4__ ipfw_table_entry ;

/* Variables and functions */
 struct table_value* get_table_value (int /*<<< orphan*/ ,struct table_config*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ipfw_export_table_value_legacy (struct table_value*) ; 
 int stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*,TYPE_5__*) ; 

__attribute__((used)) static int
dump_table_entry(void *e, void *arg)
{
	struct dump_args *da;
	struct table_config *tc;
	struct table_algo *ta;
	ipfw_table_entry *ent;
	struct table_value *pval;
	int error;

	da = (struct dump_args *)arg;

	tc = da->tc;
	ta = tc->ta;

	/* Out of memory, returning */
	if (da->cnt == da->size)
		return (1);
	ent = da->ent++;
	ent->tbl = da->uidx;
	da->cnt++;

	error = ta->dump_tentry(tc->astate, da->ti, e, &da->tent);
	if (error != 0)
		return (error);

	ent->addr = da->tent.k.addr.s_addr;
	ent->masklen = da->tent.masklen;
	pval = get_table_value(da->ch, da->tc, da->tent.v.kidx);
	ent->value = ipfw_export_table_value_legacy(pval);

	return (0);
}