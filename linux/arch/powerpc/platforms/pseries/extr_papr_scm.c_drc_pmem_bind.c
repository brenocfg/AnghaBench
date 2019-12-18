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
typedef  unsigned long uint64_t ;
struct papr_scm_priv {unsigned long bound_addr; int /*<<< orphan*/  res; int /*<<< orphan*/  drc_index; TYPE_1__* pdev; int /*<<< orphan*/  blocks; } ;
typedef  scalar_t__ int64_t ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  BIND_ANY_ADDR ; 
 scalar_t__ H_BUSY ; 
 int /*<<< orphan*/  H_SCM_BIND_MEM ; 
 int PLPAR_HCALL_BUFSIZE ; 
 int /*<<< orphan*/  cond_resched () ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ plpar_hcall (int /*<<< orphan*/ ,unsigned long*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned long) ; 

__attribute__((used)) static int drc_pmem_bind(struct papr_scm_priv *p)
{
	unsigned long ret[PLPAR_HCALL_BUFSIZE];
	uint64_t saved = 0;
	uint64_t token;
	int64_t rc;

	/*
	 * When the hypervisor cannot map all the requested memory in a single
	 * hcall it returns H_BUSY and we call again with the token until
	 * we get H_SUCCESS. Aborting the retry loop before getting H_SUCCESS
	 * leave the system in an undefined state, so we wait.
	 */
	token = 0;

	do {
		rc = plpar_hcall(H_SCM_BIND_MEM, ret, p->drc_index, 0,
				p->blocks, BIND_ANY_ADDR, token);
		token = ret[0];
		if (!saved)
			saved = ret[1];
		cond_resched();
	} while (rc == H_BUSY);

	if (rc)
		return rc;

	p->bound_addr = saved;
	dev_dbg(&p->pdev->dev, "bound drc 0x%x to %pR\n", p->drc_index, &p->res);
	return rc;
}