#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct tid_info {int dummy; } ;
struct TYPE_4__ {scalar_t__ subtype; int /*<<< orphan*/  kidx; } ;
struct table_config {int /*<<< orphan*/  astate; TYPE_1__ no; struct table_algo* ta; } ;
struct table_algo {int /*<<< orphan*/  (* foreach ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct dump_args*) ;} ;
struct ip_fw_chain {int dummy; } ;
struct dump_args {int /*<<< orphan*/  cnt; int /*<<< orphan*/  ti; int /*<<< orphan*/  size; int /*<<< orphan*/ * ent; struct table_config* tc; struct ip_fw_chain* ch; } ;
struct TYPE_5__ {int /*<<< orphan*/  cnt; int /*<<< orphan*/  size; int /*<<< orphan*/ * ent; } ;
typedef  TYPE_2__ ipfw_table ;
typedef  int /*<<< orphan*/  da ;

/* Variables and functions */
 int /*<<< orphan*/  CHAIN_TO_NI (struct ip_fw_chain*) ; 
 scalar_t__ IPFW_TABLE_ADDR ; 
 int /*<<< orphan*/  KIDX_TO_TI (struct ip_fw_chain*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dump_table_entry ; 
 struct table_config* find_table (int /*<<< orphan*/ ,struct tid_info*) ; 
 int /*<<< orphan*/  memset (struct dump_args*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct dump_args*) ; 

int
ipfw_dump_table_legacy(struct ip_fw_chain *ch, struct tid_info *ti,
    ipfw_table *tbl)
{
	struct table_config *tc;
	struct table_algo *ta;
	struct dump_args da;

	tbl->cnt = 0;

	if ((tc = find_table(CHAIN_TO_NI(ch), ti)) == NULL)
		return (0);	/* XXX: We should return ESRCH */

	ta = tc->ta;

	/* This dump format supports IPv4 only */
	if (tc->no.subtype != IPFW_TABLE_ADDR)
		return (0);

	memset(&da, 0, sizeof(da));
	da.ch = ch;
	da.ti = KIDX_TO_TI(ch, tc->no.kidx);
	da.tc = tc;
	da.ent = &tbl->ent[0];
	da.size = tbl->size;

	tbl->cnt = 0;
	ta->foreach(tc->astate, da.ti, dump_table_entry, &da);
	tbl->cnt = da.cnt;

	return (0);
}