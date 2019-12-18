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
struct tables_config {int algo_count; struct table_algo** def_algo; struct table_algo** algo; } ;
struct table_algo {size_t type; } ;
struct ip_fw_chain {int dummy; } ;

/* Variables and functions */
 struct tables_config* CHAIN_TO_TCFG (struct ip_fw_chain*) ; 
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int /*<<< orphan*/  M_IPFW ; 
 int /*<<< orphan*/  free (struct table_algo*,int /*<<< orphan*/ ) ; 

void
ipfw_del_table_algo(struct ip_fw_chain *ch, int idx)
{
	struct tables_config *tcfg;
	struct table_algo *ta;

	tcfg = CHAIN_TO_TCFG(ch);

	KASSERT(idx <= tcfg->algo_count, ("algo idx %d out of range 1..%d",
	    idx, tcfg->algo_count));

	ta = tcfg->algo[idx];
	KASSERT(ta != NULL, ("algo idx %d is NULL", idx));

	if (tcfg->def_algo[ta->type] == ta)
		tcfg->def_algo[ta->type] = NULL;

	free(ta, M_IPFW);
}