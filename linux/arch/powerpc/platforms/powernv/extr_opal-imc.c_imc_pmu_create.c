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
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_2__ {struct imc_pmu* name; } ;
struct imc_pmu {int domain; struct imc_pmu* mem_info; TYPE_1__ pmu; int /*<<< orphan*/  counter_mem_size; } ;
struct device_node {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IMC_DOMAIN_NEST ; 
 scalar_t__ imc_get_mem_addr_nest (struct device_node*,struct imc_pmu*,int /*<<< orphan*/ ) ; 
 int init_imc_pmu (struct device_node*,struct imc_pmu*,int) ; 
 int /*<<< orphan*/  kfree (struct imc_pmu*) ; 
 struct imc_pmu* kzalloc (int,int /*<<< orphan*/ ) ; 
 int of_property_read_u32 (struct device_node*,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_err (char*,struct imc_pmu*) ; 

__attribute__((used)) static int imc_pmu_create(struct device_node *parent, int pmu_index, int domain)
{
	int ret = 0;
	struct imc_pmu *pmu_ptr;
	u32 offset;

	/* Return for unknown domain */
	if (domain < 0)
		return -EINVAL;

	/* memory for pmu */
	pmu_ptr = kzalloc(sizeof(*pmu_ptr), GFP_KERNEL);
	if (!pmu_ptr)
		return -ENOMEM;

	/* Set the domain */
	pmu_ptr->domain = domain;

	ret = of_property_read_u32(parent, "size", &pmu_ptr->counter_mem_size);
	if (ret) {
		ret = -EINVAL;
		goto free_pmu;
	}

	if (!of_property_read_u32(parent, "offset", &offset)) {
		if (imc_get_mem_addr_nest(parent, pmu_ptr, offset)) {
			ret = -EINVAL;
			goto free_pmu;
		}
	}

	/* Function to register IMC pmu */
	ret = init_imc_pmu(parent, pmu_ptr, pmu_index);
	if (ret) {
		pr_err("IMC PMU %s Register failed\n", pmu_ptr->pmu.name);
		kfree(pmu_ptr->pmu.name);
		if (pmu_ptr->domain == IMC_DOMAIN_NEST)
			kfree(pmu_ptr->mem_info);
		kfree(pmu_ptr);
		return ret;
	}

	return 0;

free_pmu:
	kfree(pmu_ptr);
	return ret;
}