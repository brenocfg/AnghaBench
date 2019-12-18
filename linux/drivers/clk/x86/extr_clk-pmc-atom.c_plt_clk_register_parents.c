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
struct pmc_clk {scalar_t__ name; int /*<<< orphan*/  freq; int /*<<< orphan*/  parent_name; } ;
struct platform_device {int /*<<< orphan*/  dev; } ;
struct clk_plt_data {int nparents; int /*<<< orphan*/ * parents; } ;

/* Variables and functions */
 int ENOMEM ; 
 char const** ERR_PTR (int) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * devm_kcalloc (int /*<<< orphan*/ *,int,int,int /*<<< orphan*/ ) ; 
 char** kcalloc (int,int,int /*<<< orphan*/ ) ; 
 char* kstrdup_const (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  plt_clk_free_parent_names_loop (char const**,unsigned int) ; 
 int /*<<< orphan*/  plt_clk_register_fixed_rate (struct platform_device*,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  plt_clk_unregister_fixed_rate_loop (struct clk_plt_data*,unsigned int) ; 

__attribute__((used)) static const char **plt_clk_register_parents(struct platform_device *pdev,
					     struct clk_plt_data *data,
					     const struct pmc_clk *clks)
{
	const char **parent_names;
	unsigned int i;
	int err;
	int nparents = 0;

	data->nparents = 0;
	while (clks[nparents].name)
		nparents++;

	data->parents = devm_kcalloc(&pdev->dev, nparents,
				     sizeof(*data->parents), GFP_KERNEL);
	if (!data->parents)
		return ERR_PTR(-ENOMEM);

	parent_names = kcalloc(nparents, sizeof(*parent_names),
			       GFP_KERNEL);
	if (!parent_names)
		return ERR_PTR(-ENOMEM);

	for (i = 0; i < nparents; i++) {
		data->parents[i] =
			plt_clk_register_fixed_rate(pdev, clks[i].name,
						    clks[i].parent_name,
						    clks[i].freq);
		if (IS_ERR(data->parents[i])) {
			err = PTR_ERR(data->parents[i]);
			goto err_unreg;
		}
		parent_names[i] = kstrdup_const(clks[i].name, GFP_KERNEL);
	}

	data->nparents = nparents;
	return parent_names;

err_unreg:
	plt_clk_unregister_fixed_rate_loop(data, i);
	plt_clk_free_parent_names_loop(parent_names, i);
	return ERR_PTR(err);
}