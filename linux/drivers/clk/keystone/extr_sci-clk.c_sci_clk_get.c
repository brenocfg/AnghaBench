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
struct sci_clk_provider {int /*<<< orphan*/  num_clocks; int /*<<< orphan*/  clocks; } ;
struct clk_hw {int dummy; } ;
struct sci_clk {struct clk_hw hw; int /*<<< orphan*/  clk_id; int /*<<< orphan*/  dev_id; } ;
struct of_phandle_args {int args_count; int /*<<< orphan*/ * args; } ;
typedef  int /*<<< orphan*/  clk ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  ENODEV ; 
 struct clk_hw* ERR_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _cmp_sci_clk ; 
 struct sci_clk** bsearch (struct sci_clk*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct clk_hw *sci_clk_get(struct of_phandle_args *clkspec, void *data)
{
	struct sci_clk_provider *provider = data;
	struct sci_clk **clk;
	struct sci_clk key;

	if (clkspec->args_count != 2)
		return ERR_PTR(-EINVAL);

	key.dev_id = clkspec->args[0];
	key.clk_id = clkspec->args[1];

	clk = bsearch(&key, provider->clocks, provider->num_clocks,
		      sizeof(clk), _cmp_sci_clk);

	if (!clk)
		return ERR_PTR(-ENODEV);

	return &(*clk)->hw;
}