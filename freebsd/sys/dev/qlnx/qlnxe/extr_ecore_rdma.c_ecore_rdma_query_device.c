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
struct ecore_rdma_device {int dummy; } ;
struct ecore_hwfn {TYPE_1__* p_rdma_info; } ;
struct TYPE_2__ {struct ecore_rdma_device* dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DP_VERBOSE (struct ecore_hwfn*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ECORE_MSG_RDMA ; 

struct ecore_rdma_device *ecore_rdma_query_device(void	*rdma_cxt)
{
	struct ecore_hwfn *p_hwfn = (struct ecore_hwfn *)rdma_cxt;

	DP_VERBOSE(p_hwfn, ECORE_MSG_RDMA, "Query device\n");

	/* Return struct with device parameters */
	return p_hwfn->p_rdma_info->dev;
}