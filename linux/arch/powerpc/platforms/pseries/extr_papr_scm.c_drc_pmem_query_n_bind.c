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
struct papr_scm_priv {int blocks; int block_size; unsigned long bound_addr; TYPE_1__* pdev; int /*<<< orphan*/  res; int /*<<< orphan*/  drc_index; } ;
typedef  int int64_t ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  H_SCM_QUERY_BLOCK_MEM_BINDING ; 
 int PLPAR_HCALL_BUFSIZE ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*) ; 
 int drc_pmem_bind (struct papr_scm_priv*) ; 
 int /*<<< orphan*/  drc_pmem_unbind (struct papr_scm_priv*) ; 
 int plpar_hcall (int /*<<< orphan*/ ,unsigned long*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int drc_pmem_query_n_bind(struct papr_scm_priv *p)
{
	unsigned long start_addr;
	unsigned long end_addr;
	unsigned long ret[PLPAR_HCALL_BUFSIZE];
	int64_t rc;


	rc = plpar_hcall(H_SCM_QUERY_BLOCK_MEM_BINDING, ret,
			 p->drc_index, 0);
	if (rc)
		goto err_out;
	start_addr = ret[0];

	/* Make sure the full region is bound. */
	rc = plpar_hcall(H_SCM_QUERY_BLOCK_MEM_BINDING, ret,
			 p->drc_index, p->blocks - 1);
	if (rc)
		goto err_out;
	end_addr = ret[0];

	if ((end_addr - start_addr) != ((p->blocks - 1) * p->block_size))
		goto err_out;

	p->bound_addr = start_addr;
	dev_dbg(&p->pdev->dev, "bound drc 0x%x to %pR\n", p->drc_index, &p->res);
	return rc;

err_out:
	dev_info(&p->pdev->dev,
		 "Failed to query, trying an unbind followed by bind");
	drc_pmem_unbind(p);
	return drc_pmem_bind(p);
}