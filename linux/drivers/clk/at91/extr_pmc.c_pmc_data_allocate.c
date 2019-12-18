#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct pmc_data {unsigned int ncore; unsigned int nsystem; unsigned int nperiph; unsigned int ngck; void* ghws; void* phws; void* shws; void* chws; } ;
struct clk_hw {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 void* kcalloc (unsigned int,int,int /*<<< orphan*/ ) ; 
 struct pmc_data* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pmc_data_free (struct pmc_data*) ; 

struct pmc_data *pmc_data_allocate(unsigned int ncore, unsigned int nsystem,
				   unsigned int nperiph, unsigned int ngck)
{
	struct pmc_data *pmc_data = kzalloc(sizeof(*pmc_data), GFP_KERNEL);

	if (!pmc_data)
		return NULL;

	pmc_data->ncore = ncore;
	pmc_data->chws = kcalloc(ncore, sizeof(struct clk_hw *), GFP_KERNEL);
	if (!pmc_data->chws)
		goto err;

	pmc_data->nsystem = nsystem;
	pmc_data->shws = kcalloc(nsystem, sizeof(struct clk_hw *), GFP_KERNEL);
	if (!pmc_data->shws)
		goto err;

	pmc_data->nperiph = nperiph;
	pmc_data->phws = kcalloc(nperiph, sizeof(struct clk_hw *), GFP_KERNEL);
	if (!pmc_data->phws)
		goto err;

	pmc_data->ngck = ngck;
	pmc_data->ghws = kcalloc(ngck, sizeof(struct clk_hw *), GFP_KERNEL);
	if (!pmc_data->ghws)
		goto err;

	return pmc_data;

err:
	pmc_data_free(pmc_data);

	return NULL;
}