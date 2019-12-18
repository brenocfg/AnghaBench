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
typedef  int /*<<< orphan*/  uint32_t ;
struct table_info {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  kidx; } ;
struct table_config {int /*<<< orphan*/  astate; int /*<<< orphan*/  count; struct table_algo* ta; TYPE_1__ no; } ;
struct table_algo {int flags; int /*<<< orphan*/  (* foreach ) (int /*<<< orphan*/ ,struct table_info*,int /*<<< orphan*/ ,struct dump_args*) ;int /*<<< orphan*/  (* get_count ) (int /*<<< orphan*/ ,struct table_info*) ;} ;
struct ip_fw_chain {int dummy; } ;
struct dump_args {int /*<<< orphan*/  cnt; } ;
typedef  int /*<<< orphan*/  da ;

/* Variables and functions */
 struct table_info* KIDX_TO_TI (struct ip_fw_chain*,int /*<<< orphan*/ ) ; 
 int TA_FLAG_EXTCOUNTER ; 
 int TA_FLAG_READONLY ; 
 int /*<<< orphan*/  count_ext_entries ; 
 int /*<<< orphan*/  memset (struct dump_args*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,struct table_info*) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ ,struct table_info*,int /*<<< orphan*/ ,struct dump_args*) ; 

__attribute__((used)) static uint32_t
table_get_count(struct ip_fw_chain *ch, struct table_config *tc)
{
	struct table_info *ti;
	struct table_algo *ta;
	struct dump_args da;

	ti = KIDX_TO_TI(ch, tc->no.kidx);
	ta = tc->ta;

	/* Use internal counter for self-managed tables */
	if ((ta->flags & TA_FLAG_READONLY) == 0)
		return (tc->count);

	/* Use callback to quickly get number of items */
	if ((ta->flags & TA_FLAG_EXTCOUNTER) != 0)
		return (ta->get_count(tc->astate, ti));

	/* Count number of iterms ourselves */
	memset(&da, 0, sizeof(da));
	ta->foreach(tc->astate, ti, count_ext_entries, &da);

	return (da.cnt);
}