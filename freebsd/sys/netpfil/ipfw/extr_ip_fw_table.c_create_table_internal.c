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
typedef  int /*<<< orphan*/  uint16_t ;
struct tid_info {int dummy; } ;
struct TYPE_4__ {scalar_t__ subtype; int /*<<< orphan*/  kidx; int /*<<< orphan*/  refcnt; int /*<<< orphan*/  etlv; } ;
struct table_config {int locked; TYPE_1__ no; int /*<<< orphan*/  limit; int /*<<< orphan*/  vmask; } ;
struct table_algo {int flags; } ;
struct namedobj_instance {int dummy; } ;
struct ip_fw_chain {int dummy; } ;
struct TYPE_5__ {int flags; int /*<<< orphan*/  limit; int /*<<< orphan*/  vmask; int /*<<< orphan*/  tflags; } ;
typedef  TYPE_2__ ipfw_xtable_info ;

/* Variables and functions */
 struct namedobj_instance* CHAIN_TO_NI (struct ip_fw_chain*) ; 
 int /*<<< orphan*/  CHAIN_TO_TCFG (struct ip_fw_chain*) ; 
 int EBUSY ; 
 int EEXIST ; 
 int ENOMEM ; 
 int ENOTSUP ; 
 int IPFW_TGFLAGS_LOCKED ; 
 int /*<<< orphan*/  IPFW_TLV_TBL_NAME ; 
 int /*<<< orphan*/  IPFW_UH_WLOCK (struct ip_fw_chain*) ; 
 int /*<<< orphan*/  IPFW_UH_WUNLOCK (struct ip_fw_chain*) ; 
 int TA_FLAG_READONLY ; 
 struct table_config* alloc_table_config (struct ip_fw_chain*,struct tid_info*,struct table_algo*,char*,int /*<<< orphan*/ ) ; 
 struct table_config* find_table (struct namedobj_instance*,struct tid_info*) ; 
 struct table_algo* find_table_algo (int /*<<< orphan*/ ,struct tid_info*,char*) ; 
 int /*<<< orphan*/  free_table_config (struct namedobj_instance*,struct table_config*) ; 
 scalar_t__ ipfw_objhash_alloc_idx (struct namedobj_instance*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  link_table (struct ip_fw_chain*,struct table_config*) ; 
 int /*<<< orphan*/  printf (char*) ; 

__attribute__((used)) static int
create_table_internal(struct ip_fw_chain *ch, struct tid_info *ti,
    char *aname, ipfw_xtable_info *i, uint16_t *pkidx, int compat)
{
	struct namedobj_instance *ni;
	struct table_config *tc, *tc_new, *tmp;
	struct table_algo *ta;
	uint16_t kidx;

	ni = CHAIN_TO_NI(ch);

	ta = find_table_algo(CHAIN_TO_TCFG(ch), ti, aname);
	if (ta == NULL)
		return (ENOTSUP);

	tc = alloc_table_config(ch, ti, ta, aname, i->tflags);
	if (tc == NULL)
		return (ENOMEM);

	tc->vmask = i->vmask;
	tc->limit = i->limit;
	if (ta->flags & TA_FLAG_READONLY)
		tc->locked = 1;
	else
		tc->locked = (i->flags & IPFW_TGFLAGS_LOCKED) != 0;

	IPFW_UH_WLOCK(ch);

	/* Check if table has been already created */
	tc_new = find_table(ni, ti);
	if (tc_new != NULL) {

		/*
		 * Compat: do not fail if we're
		 * requesting to create existing table
		 * which has the same type
		 */
		if (compat == 0 || tc_new->no.subtype != tc->no.subtype) {
			IPFW_UH_WUNLOCK(ch);
			free_table_config(ni, tc);
			return (EEXIST);
		}

		/* Exchange tc and tc_new for proper refcounting & freeing */
		tmp = tc;
		tc = tc_new;
		tc_new = tmp;
	} else {
		/* New table */
		if (ipfw_objhash_alloc_idx(ni, &kidx) != 0) {
			IPFW_UH_WUNLOCK(ch);
			printf("Unable to allocate table index."
			    " Consider increasing net.inet.ip.fw.tables_max");
			free_table_config(ni, tc);
			return (EBUSY);
		}
		tc->no.kidx = kidx;
		tc->no.etlv = IPFW_TLV_TBL_NAME;

		link_table(ch, tc);
	}

	if (compat != 0)
		tc->no.refcnt++;
	if (pkidx != NULL)
		*pkidx = tc->no.kidx;

	IPFW_UH_WUNLOCK(ch);

	if (tc_new != NULL)
		free_table_config(ni, tc_new);

	return (0);
}