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
struct papr_scm_priv {int /*<<< orphan*/  drc_index; TYPE_1__* pdev; } ;
typedef  scalar_t__ int64_t ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 scalar_t__ H_BUSY ; 
 scalar_t__ H_IS_LONG_BUSY (scalar_t__) ; 
 int /*<<< orphan*/  H_SCM_UNBIND_ALL ; 
 int /*<<< orphan*/  H_UNBIND_SCOPE_DRC ; 
 int PLPAR_HCALL_BUFSIZE ; 
 int /*<<< orphan*/  cond_resched () ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,scalar_t__) ; 
 int /*<<< orphan*/  get_longbusy_msecs (scalar_t__) ; 
 int /*<<< orphan*/  msleep (int /*<<< orphan*/ ) ; 
 scalar_t__ plpar_hcall (int /*<<< orphan*/ ,unsigned long*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned long) ; 

__attribute__((used)) static void drc_pmem_unbind(struct papr_scm_priv *p)
{
	unsigned long ret[PLPAR_HCALL_BUFSIZE];
	uint64_t token = 0;
	int64_t rc;

	dev_dbg(&p->pdev->dev, "unbind drc 0x%x\n", p->drc_index);

	/* NB: unbind has the same retry requirements as drc_pmem_bind() */
	do {

		/* Unbind of all SCM resources associated with drcIndex */
		rc = plpar_hcall(H_SCM_UNBIND_ALL, ret, H_UNBIND_SCOPE_DRC,
				 p->drc_index, token);
		token = ret[0];

		/* Check if we are stalled for some time */
		if (H_IS_LONG_BUSY(rc)) {
			msleep(get_longbusy_msecs(rc));
			rc = H_BUSY;
		} else if (rc == H_BUSY) {
			cond_resched();
		}

	} while (rc == H_BUSY);

	if (rc)
		dev_err(&p->pdev->dev, "unbind error: %lld\n", rc);
	else
		dev_dbg(&p->pdev->dev, "unbind drc 0x%x complete\n",
			p->drc_index);

	return;
}