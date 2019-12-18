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
struct table_value {int dummy; } ;
struct table_config {int dummy; } ;
struct namedobj_instance {int dummy; } ;
struct ip_fw_chain {scalar_t__ valuestate; } ;

/* Variables and functions */
 struct namedobj_instance* CHAIN_TO_VI (struct ip_fw_chain*) ; 

__attribute__((used)) static void
get_value_ptrs(struct ip_fw_chain *ch, struct table_config *tc, int vshared,
    struct table_value **ptv, struct namedobj_instance **pvi)
{
	struct table_value *pval;
	struct namedobj_instance *vi;

	if (vshared != 0) {
		pval = (struct table_value *)ch->valuestate;
		vi = CHAIN_TO_VI(ch);
	} else {
		pval = NULL;
		vi = NULL;
		//pval = (struct table_value *)&tc->ti.data;
	}

	if (ptv != NULL)
		*ptv = pval;
	if (pvi != NULL)
		*pvi = vi;
}