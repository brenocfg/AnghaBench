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
typedef  int /*<<< orphan*/  uint16_t ;
struct tid_info {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  kidx; } ;
struct table_config {TYPE_1__ no; } ;
struct ip_fw_chain {int dummy; } ;
typedef  int /*<<< orphan*/  ipfw_obj_ntlv ;

/* Variables and functions */
 int /*<<< orphan*/  CHAIN_TO_NI (struct ip_fw_chain*) ; 
 int ESRCH ; 
 int /*<<< orphan*/  IPFW_UH_WLOCK_ASSERT (struct ip_fw_chain*) ; 
 int find_table_err (int /*<<< orphan*/ ,struct tid_info*,struct table_config**) ; 
 int /*<<< orphan*/  ntlv_to_ti (int /*<<< orphan*/ *,struct tid_info*) ; 
 int /*<<< orphan*/  tc_ref (struct table_config*) ; 

int
ipfw_ref_table(struct ip_fw_chain *ch, ipfw_obj_ntlv *ntlv, uint16_t *kidx)
{
	struct tid_info ti;
	struct table_config *tc;
	int error;

	IPFW_UH_WLOCK_ASSERT(ch);

	ntlv_to_ti(ntlv, &ti);
	error = find_table_err(CHAIN_TO_NI(ch), &ti, &tc);
	if (error != 0)
		return (error);

	if (tc == NULL)
		return (ESRCH);

	tc_ref(tc);
	*kidx = tc->no.kidx;

	return (0);
}