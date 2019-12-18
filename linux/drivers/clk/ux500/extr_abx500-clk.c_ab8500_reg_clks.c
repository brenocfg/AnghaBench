#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
typedef  int /*<<< orphan*/  u16 ;
struct device_node {int dummy; } ;
struct device {struct device_node* of_node; } ;
struct clk {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  clk_num; struct clk** clks; } ;

/* Variables and functions */
 int /*<<< orphan*/  AB8500_SWATCTRL ; 
 int /*<<< orphan*/  AB8500_SWATCTRL_SWATENABLE ; 
 size_t AB8500_SYSCLK_AUDIO ; 
 size_t AB8500_SYSCLK_BUF2 ; 
 size_t AB8500_SYSCLK_BUF3 ; 
 size_t AB8500_SYSCLK_BUF4 ; 
 size_t AB8500_SYSCLK_INT ; 
 size_t AB8500_SYSCLK_ULP ; 
 int /*<<< orphan*/  AB8500_SYSULPCLKCTRL1 ; 
 int /*<<< orphan*/  AB8500_SYSULPCLKCTRL1_AUDIOCLKENA ; 
 int /*<<< orphan*/  AB8500_SYSULPCLKCTRL1_SYSCLKBUF2REQ ; 
 int /*<<< orphan*/  AB8500_SYSULPCLKCTRL1_SYSCLKBUF3REQ ; 
 int /*<<< orphan*/  AB8500_SYSULPCLKCTRL1_SYSCLKBUF4REQ ; 
 int AB8500_SYSULPCLKCTRL1_SYSULPCLKINTSEL_MASK ; 
 int AB8500_SYSULPCLKCTRL1_SYSULPCLKINTSEL_SHIFT ; 
 int /*<<< orphan*/  AB8500_SYSULPCLKCTRL1_ULPCLKREQ ; 
 int /*<<< orphan*/  ARRAY_SIZE (struct clk**) ; 
 TYPE_1__ ab8500_clk_data ; 
 struct clk** ab8500_clks ; 
 int ab8500_sysctrl_set (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct clk* clk_reg_sysctrl_gate (struct device*,char*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct clk* clk_reg_sysctrl_gate_fixed_rate (struct device*,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ) ; 
 struct clk* clk_reg_sysctrl_set_parent (struct device*,char*,char const**,int,int /*<<< orphan*/ *,int*,int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_info (struct device*,char*) ; 
 int /*<<< orphan*/  of_clk_add_provider (struct device_node*,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  of_clk_src_onecell_get ; 

__attribute__((used)) static int ab8500_reg_clks(struct device *dev)
{
	int ret;
	struct clk *clk;
	struct device_node *np = dev->of_node;
	const char *intclk_parents[] = {"ab8500_sysclk", "ulpclk"};
	u16 intclk_reg_sel[] = {0 , AB8500_SYSULPCLKCTRL1};
	u8 intclk_reg_mask[] = {0 , AB8500_SYSULPCLKCTRL1_SYSULPCLKINTSEL_MASK};
	u8 intclk_reg_bits[] = {
		0 ,
		(1 << AB8500_SYSULPCLKCTRL1_SYSULPCLKINTSEL_SHIFT)
	};

	/* Enable SWAT */
	ret = ab8500_sysctrl_set(AB8500_SWATCTRL, AB8500_SWATCTRL_SWATENABLE);
	if (ret)
		return ret;

	/* ab8500_sysclk2 */
	clk = clk_reg_sysctrl_gate(dev , "ab8500_sysclk2", "ab8500_sysclk",
		AB8500_SYSULPCLKCTRL1, AB8500_SYSULPCLKCTRL1_SYSCLKBUF2REQ,
		AB8500_SYSULPCLKCTRL1_SYSCLKBUF2REQ, 0, 0);
	ab8500_clks[AB8500_SYSCLK_BUF2] = clk;

	/* ab8500_sysclk3 */
	clk = clk_reg_sysctrl_gate(dev , "ab8500_sysclk3", "ab8500_sysclk",
		AB8500_SYSULPCLKCTRL1, AB8500_SYSULPCLKCTRL1_SYSCLKBUF3REQ,
		AB8500_SYSULPCLKCTRL1_SYSCLKBUF3REQ, 0, 0);
	ab8500_clks[AB8500_SYSCLK_BUF3] = clk;

	/* ab8500_sysclk4 */
	clk = clk_reg_sysctrl_gate(dev , "ab8500_sysclk4", "ab8500_sysclk",
		AB8500_SYSULPCLKCTRL1, AB8500_SYSULPCLKCTRL1_SYSCLKBUF4REQ,
		AB8500_SYSULPCLKCTRL1_SYSCLKBUF4REQ, 0, 0);
	ab8500_clks[AB8500_SYSCLK_BUF4] = clk;

	/* ab_ulpclk */
	clk = clk_reg_sysctrl_gate_fixed_rate(dev, "ulpclk", NULL,
		AB8500_SYSULPCLKCTRL1, AB8500_SYSULPCLKCTRL1_ULPCLKREQ,
		AB8500_SYSULPCLKCTRL1_ULPCLKREQ,
		38400000, 9000, 0);
	ab8500_clks[AB8500_SYSCLK_ULP] = clk;

	/* ab8500_intclk */
	clk = clk_reg_sysctrl_set_parent(dev , "intclk", intclk_parents, 2,
		intclk_reg_sel, intclk_reg_mask, intclk_reg_bits, 0);
	ab8500_clks[AB8500_SYSCLK_INT] = clk;

	/* ab8500_audioclk */
	clk = clk_reg_sysctrl_gate(dev , "audioclk", "intclk",
		AB8500_SYSULPCLKCTRL1, AB8500_SYSULPCLKCTRL1_AUDIOCLKENA,
		AB8500_SYSULPCLKCTRL1_AUDIOCLKENA, 0, 0);
	ab8500_clks[AB8500_SYSCLK_AUDIO] = clk;

	ab8500_clk_data.clks = ab8500_clks;
	ab8500_clk_data.clk_num = ARRAY_SIZE(ab8500_clks);
	of_clk_add_provider(np, of_clk_src_onecell_get, &ab8500_clk_data);

	dev_info(dev, "registered clocks for ab850x\n");

	return 0;
}