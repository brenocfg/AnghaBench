#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct tentry_info {scalar_t__ value; } ;
struct tableop_state {int count; struct tentry_info* tei; int /*<<< orphan*/  vshared; int /*<<< orphan*/  tc; struct ip_fw_chain* ch; } ;
struct table_value {int dummy; } ;
struct namedobj_instance {int dummy; } ;
struct ip_fw_chain {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  IPFW_UH_WLOCK_ASSERT (struct ip_fw_chain*) ; 
 int /*<<< orphan*/  get_value_ptrs (struct ip_fw_chain*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct table_value**,struct namedobj_instance**) ; 
 int /*<<< orphan*/  unref_table_value (struct namedobj_instance*,struct table_value*,scalar_t__) ; 

void
rollback_table_values(struct tableop_state *ts)
{
	struct ip_fw_chain *ch;
	struct table_value *pval;
	struct tentry_info *ptei;
	struct namedobj_instance *vi;
	int i;

	ch = ts->ch;

	IPFW_UH_WLOCK_ASSERT(ch);

	/* Get current table value pointer */
	get_value_ptrs(ch, ts->tc, ts->vshared, &pval, &vi);

	for (i = 0; i < ts->count; i++) {
		ptei = &ts->tei[i];

		if (ptei->value == 0)
			continue;

		unref_table_value(vi, pval, ptei->value);
	}
}