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
struct hi6220_stub_clk {int /*<<< orphan*/  dfs_map; } ;

/* Variables and functions */
 int /*<<< orphan*/  ACPU_DFS_FLAG ; 
 int /*<<< orphan*/  ACPU_DFS_FREQ_LMT ; 
 int /*<<< orphan*/  ACPU_DFS_FREQ_MAX ; 
 unsigned int ACPU_DFS_LOCK_FLAG ; 
 unsigned int UINT_MAX ; 
 scalar_t__ WARN_ON (int) ; 
 unsigned int min (unsigned int,unsigned int) ; 
 int /*<<< orphan*/  regmap_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int*) ; 

__attribute__((used)) static int hi6220_acpu_round_freq(struct hi6220_stub_clk *stub_clk,
				  unsigned int freq)
{
	unsigned int limit_flag, limit_freq = UINT_MAX;
	unsigned int max_freq;

	/* check the constrained frequency */
	regmap_read(stub_clk->dfs_map, ACPU_DFS_FLAG, &limit_flag);
	if (limit_flag == ACPU_DFS_LOCK_FLAG)
		regmap_read(stub_clk->dfs_map, ACPU_DFS_FREQ_LMT, &limit_freq);

	/* check the supported maximum frequency */
	regmap_read(stub_clk->dfs_map, ACPU_DFS_FREQ_MAX, &max_freq);

	/* calculate the real maximum frequency */
	max_freq = min(max_freq, limit_freq);

	if (WARN_ON(freq > max_freq))
		freq = max_freq;

	return freq;
}