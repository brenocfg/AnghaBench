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
struct regmap {int dummy; } ;
struct clk_init_data {char const* name; char const** parent_names; int num_parents; scalar_t__ flags; int /*<<< orphan*/ * ops; } ;
struct clk_hw {struct clk_init_data* init; } ;
struct clk_gemini_pci {struct clk_hw hw; struct regmap* map; } ;

/* Variables and functions */
 int ENOMEM ; 
 struct clk_hw* ERR_PTR (int) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int clk_hw_register (int /*<<< orphan*/ *,struct clk_hw*) ; 
 int /*<<< orphan*/  gemini_pci_clk_ops ; 
 int /*<<< orphan*/  kfree (struct clk_gemini_pci*) ; 
 struct clk_gemini_pci* kzalloc (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct clk_hw *gemini_pci_clk_setup(const char *name,
					   const char *parent_name,
					   struct regmap *map)
{
	struct clk_gemini_pci *pciclk;
	struct clk_init_data init;
	int ret;

	pciclk = kzalloc(sizeof(*pciclk), GFP_KERNEL);
	if (!pciclk)
		return ERR_PTR(-ENOMEM);

	init.name = name;
	init.ops = &gemini_pci_clk_ops;
	init.flags = 0;
	init.parent_names = &parent_name;
	init.num_parents = 1;
	pciclk->map = map;
	pciclk->hw.init = &init;

	ret = clk_hw_register(NULL, &pciclk->hw);
	if (ret) {
		kfree(pciclk);
		return ERR_PTR(ret);
	}

	return &pciclk->hw;
}