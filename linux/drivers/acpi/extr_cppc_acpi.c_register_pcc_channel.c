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
typedef  int u64 ;
struct acpi_pcct_hw_reduced {int latency; int /*<<< orphan*/  length; int /*<<< orphan*/  base_address; int /*<<< orphan*/  max_access_rate; int /*<<< orphan*/  min_turnaround_time; } ;
struct TYPE_5__ {int deadline_us; int pcc_nominal; int pcc_channel_acquired; int /*<<< orphan*/  pcc_comm_addr; int /*<<< orphan*/  pcc_mpar; int /*<<< orphan*/  pcc_mrtt; TYPE_1__* pcc_channel; } ;
struct TYPE_4__ {struct acpi_pcct_hw_reduced* con_priv; } ;

/* Variables and functions */
 int ENODEV ; 
 int ENOMEM ; 
 scalar_t__ IS_ERR (TYPE_1__*) ; 
 int NUM_RETRIES ; 
 int /*<<< orphan*/  acpi_os_ioremap (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cppc_mbox_cl ; 
 TYPE_2__** pcc_data ; 
 TYPE_1__* pcc_mbox_request_channel (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  pr_err (char*,int) ; 

__attribute__((used)) static int register_pcc_channel(int pcc_ss_idx)
{
	struct acpi_pcct_hw_reduced *cppc_ss;
	u64 usecs_lat;

	if (pcc_ss_idx >= 0) {
		pcc_data[pcc_ss_idx]->pcc_channel =
			pcc_mbox_request_channel(&cppc_mbox_cl,	pcc_ss_idx);

		if (IS_ERR(pcc_data[pcc_ss_idx]->pcc_channel)) {
			pr_err("Failed to find PCC channel for subspace %d\n",
			       pcc_ss_idx);
			return -ENODEV;
		}

		/*
		 * The PCC mailbox controller driver should
		 * have parsed the PCCT (global table of all
		 * PCC channels) and stored pointers to the
		 * subspace communication region in con_priv.
		 */
		cppc_ss = (pcc_data[pcc_ss_idx]->pcc_channel)->con_priv;

		if (!cppc_ss) {
			pr_err("No PCC subspace found for %d CPPC\n",
			       pcc_ss_idx);
			return -ENODEV;
		}

		/*
		 * cppc_ss->latency is just a Nominal value. In reality
		 * the remote processor could be much slower to reply.
		 * So add an arbitrary amount of wait on top of Nominal.
		 */
		usecs_lat = NUM_RETRIES * cppc_ss->latency;
		pcc_data[pcc_ss_idx]->deadline_us = usecs_lat;
		pcc_data[pcc_ss_idx]->pcc_mrtt = cppc_ss->min_turnaround_time;
		pcc_data[pcc_ss_idx]->pcc_mpar = cppc_ss->max_access_rate;
		pcc_data[pcc_ss_idx]->pcc_nominal = cppc_ss->latency;

		pcc_data[pcc_ss_idx]->pcc_comm_addr =
			acpi_os_ioremap(cppc_ss->base_address, cppc_ss->length);
		if (!pcc_data[pcc_ss_idx]->pcc_comm_addr) {
			pr_err("Failed to ioremap PCC comm region mem for %d\n",
			       pcc_ss_idx);
			return -ENOMEM;
		}

		/* Set flag so that we don't come here for each CPU. */
		pcc_data[pcc_ss_idx]->pcc_channel_acquired = true;
	}

	return 0;
}