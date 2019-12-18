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
struct tegra_bpmp_clk_info {int flags; unsigned int num_parents; unsigned int* parents; int /*<<< orphan*/  name; int /*<<< orphan*/  id; } ;
struct tegra_bpmp {int /*<<< orphan*/  dev; } ;
struct seq_buf {int dummy; } ;
typedef  int /*<<< orphan*/  flags ;

/* Variables and functions */
 int TEGRA_BPMP_CLK_HAS_MUX ; 
 int TEGRA_BPMP_CLK_HAS_SET_RATE ; 
 int TEGRA_BPMP_CLK_IS_ROOT ; 
 int /*<<< orphan*/  dev_printk (char const*,int /*<<< orphan*/ ,char*,unsigned int,...) ; 
 int /*<<< orphan*/  seq_buf_init (struct seq_buf*,char*,int) ; 
 int /*<<< orphan*/  seq_buf_printf (struct seq_buf*,char*,...) ; 

__attribute__((used)) static void tegra_bpmp_clk_info_dump(struct tegra_bpmp *bpmp,
				     const char *level,
				     const struct tegra_bpmp_clk_info *info)
{
	const char *prefix = "";
	struct seq_buf buf;
	unsigned int i;
	char flags[64];

	seq_buf_init(&buf, flags, sizeof(flags));

	if (info->flags)
		seq_buf_printf(&buf, "(");

	if (info->flags & TEGRA_BPMP_CLK_HAS_MUX) {
		seq_buf_printf(&buf, "%smux", prefix);
		prefix = ", ";
	}

	if ((info->flags & TEGRA_BPMP_CLK_HAS_SET_RATE) == 0) {
		seq_buf_printf(&buf, "%sfixed", prefix);
		prefix = ", ";
	}

	if (info->flags & TEGRA_BPMP_CLK_IS_ROOT) {
		seq_buf_printf(&buf, "%sroot", prefix);
		prefix = ", ";
	}

	if (info->flags)
		seq_buf_printf(&buf, ")");

	dev_printk(level, bpmp->dev, "%03u: %s\n", info->id, info->name);
	dev_printk(level, bpmp->dev, "  flags: %lx %s\n", info->flags, flags);
	dev_printk(level, bpmp->dev, "  parents: %u\n", info->num_parents);

	for (i = 0; i < info->num_parents; i++)
		dev_printk(level, bpmp->dev, "    %03u\n", info->parents[i]);
}