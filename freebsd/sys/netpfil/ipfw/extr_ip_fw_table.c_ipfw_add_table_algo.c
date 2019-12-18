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
struct table_algo {scalar_t__ type; size_t idx; int flags; int /*<<< orphan*/  ta_buf_size; } ;
struct ip_fw_chain {int dummy; } ;

/* Variables and functions */
 struct tables_config* CHAIN_TO_TCFG (struct ip_fw_chain*) ; 
 int EINVAL ; 
 scalar_t__ IPFW_TABLE_MAXTYPE ; 
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int /*<<< orphan*/  M_IPFW ; 
 int M_WAITOK ; 
 int M_ZERO ; 
 size_t TA_BUF_SZ ; 
 int TA_FLAG_DEFAULT ; 
 struct table_algo* malloc (int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  memcpy (struct table_algo*,struct table_algo*,size_t) ; 
 size_t roundup2 (int /*<<< orphan*/ ,int) ; 

int
ipfw_add_table_algo(struct ip_fw_chain *ch, struct table_algo *ta, size_t size,
    int *idx)
{
	struct tables_config *tcfg;
	struct table_algo *ta_new;
	size_t sz;

	if (size > sizeof(struct table_algo))
		return (EINVAL);

	/* Check for the required on-stack size for add/del */
	sz = roundup2(ta->ta_buf_size, sizeof(void *));
	if (sz > TA_BUF_SZ)
		return (EINVAL);

	KASSERT(ta->type <= IPFW_TABLE_MAXTYPE,("Increase IPFW_TABLE_MAXTYPE"));

	/* Copy algorithm data to stable storage. */
	ta_new = malloc(sizeof(struct table_algo), M_IPFW, M_WAITOK | M_ZERO);
	memcpy(ta_new, ta, size);

	tcfg = CHAIN_TO_TCFG(ch);

	KASSERT(tcfg->algo_count < 255, ("Increase algo array size"));

	tcfg->algo[++tcfg->algo_count] = ta_new;
	ta_new->idx = tcfg->algo_count;

	/* Set algorithm as default one for given type */
	if ((ta_new->flags & TA_FLAG_DEFAULT) != 0 &&
	    tcfg->def_algo[ta_new->type] == NULL)
		tcfg->def_algo[ta_new->type] = ta_new;

	*idx = ta_new->idx;
	
	return (0);
}