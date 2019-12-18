#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u64 ;
struct seq_file {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/ * i_lcoefs; } ;
struct ioc {scalar_t__ user_cost_model; TYPE_1__ params; } ;
struct blkg_policy_data {int /*<<< orphan*/  blkg; } ;
struct TYPE_4__ {struct ioc* ioc; } ;

/* Variables and functions */
 size_t I_LCOEF_RBPS ; 
 size_t I_LCOEF_RRANDIOPS ; 
 size_t I_LCOEF_RSEQIOPS ; 
 size_t I_LCOEF_WBPS ; 
 size_t I_LCOEF_WRANDIOPS ; 
 size_t I_LCOEF_WSEQIOPS ; 
 char* blkg_dev_name (int /*<<< orphan*/ ) ; 
 TYPE_2__* pd_to_iocg (struct blkg_policy_data*) ; 
 int /*<<< orphan*/  seq_printf (struct seq_file*,char*,char const*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static u64 ioc_cost_model_prfill(struct seq_file *sf,
				 struct blkg_policy_data *pd, int off)
{
	const char *dname = blkg_dev_name(pd->blkg);
	struct ioc *ioc = pd_to_iocg(pd)->ioc;
	u64 *u = ioc->params.i_lcoefs;

	if (!dname)
		return 0;

	seq_printf(sf, "%s ctrl=%s model=linear "
		   "rbps=%llu rseqiops=%llu rrandiops=%llu "
		   "wbps=%llu wseqiops=%llu wrandiops=%llu\n",
		   dname, ioc->user_cost_model ? "user" : "auto",
		   u[I_LCOEF_RBPS], u[I_LCOEF_RSEQIOPS], u[I_LCOEF_RRANDIOPS],
		   u[I_LCOEF_WBPS], u[I_LCOEF_WSEQIOPS], u[I_LCOEF_WRANDIOPS]);
	return 0;
}