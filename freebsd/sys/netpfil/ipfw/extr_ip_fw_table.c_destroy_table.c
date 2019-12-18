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
struct tid_info {int dummy; } ;
struct TYPE_2__ {scalar_t__ refcnt; int kidx; } ;
struct table_config {char* tablename; int /*<<< orphan*/  ti_copy; int /*<<< orphan*/  astate; int /*<<< orphan*/  ta; TYPE_1__ no; } ;
struct namedobj_instance {int dummy; } ;
struct ip_fw_chain {int dummy; } ;

/* Variables and functions */
 struct namedobj_instance* CHAIN_TO_NI (struct ip_fw_chain*) ; 
 int EBUSY ; 
 int ESRCH ; 
 int /*<<< orphan*/  IPFW_UH_WLOCK (struct ip_fw_chain*) ; 
 int /*<<< orphan*/  IPFW_UH_WUNLOCK (struct ip_fw_chain*) ; 
 int /*<<< orphan*/  IPFW_WLOCK (struct ip_fw_chain*) ; 
 int /*<<< orphan*/  IPFW_WUNLOCK (struct ip_fw_chain*) ; 
 struct table_config* find_table (struct namedobj_instance*,struct tid_info*) ; 
 int /*<<< orphan*/  free_table_config (struct namedobj_instance*,struct table_config*) ; 
 scalar_t__ ipfw_objhash_free_idx (struct namedobj_instance*,int) ; 
 int /*<<< orphan*/  ipfw_unref_table_values (struct ip_fw_chain*,struct table_config*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  printf (char*,int,char*) ; 
 int /*<<< orphan*/  unlink_table (struct ip_fw_chain*,struct table_config*) ; 

__attribute__((used)) static int
destroy_table(struct ip_fw_chain *ch, struct tid_info *ti)
{
	struct namedobj_instance *ni;
	struct table_config *tc;

	IPFW_UH_WLOCK(ch);

	ni = CHAIN_TO_NI(ch);
	if ((tc = find_table(ni, ti)) == NULL) {
		IPFW_UH_WUNLOCK(ch);
		return (ESRCH);
	}

	/* Do not permit destroying referenced tables */
	if (tc->no.refcnt > 0) {
		IPFW_UH_WUNLOCK(ch);
		return (EBUSY);
	}

	IPFW_WLOCK(ch);
	unlink_table(ch, tc);
	IPFW_WUNLOCK(ch);

	/* Free obj index */
	if (ipfw_objhash_free_idx(ni, tc->no.kidx) != 0)
		printf("Error unlinking kidx %d from table %s\n",
		    tc->no.kidx, tc->tablename);

	/* Unref values used in tables while holding UH lock */
	ipfw_unref_table_values(ch, tc, tc->ta, tc->astate, &tc->ti_copy);
	IPFW_UH_WUNLOCK(ch);

	free_table_config(ni, tc);

	return (0);
}