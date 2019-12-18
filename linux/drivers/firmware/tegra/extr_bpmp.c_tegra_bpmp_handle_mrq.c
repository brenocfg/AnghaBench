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
typedef  int /*<<< orphan*/  zero ;
typedef  int /*<<< orphan*/  u32 ;
struct tegra_bpmp_mrq {int /*<<< orphan*/  data; int /*<<< orphan*/  (* handler ) (unsigned int,struct tegra_bpmp_channel*,int /*<<< orphan*/ ) ;} ;
struct tegra_bpmp_channel {int dummy; } ;
struct tegra_bpmp {int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (unsigned int,struct tegra_bpmp_channel*,int /*<<< orphan*/ ) ; 
 struct tegra_bpmp_mrq* tegra_bpmp_find_mrq (struct tegra_bpmp*,unsigned int) ; 
 int /*<<< orphan*/  tegra_bpmp_mrq_return (struct tegra_bpmp_channel*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void tegra_bpmp_handle_mrq(struct tegra_bpmp *bpmp,
				  unsigned int mrq,
				  struct tegra_bpmp_channel *channel)
{
	struct tegra_bpmp_mrq *entry;
	u32 zero = 0;

	spin_lock(&bpmp->lock);

	entry = tegra_bpmp_find_mrq(bpmp, mrq);
	if (!entry) {
		spin_unlock(&bpmp->lock);
		tegra_bpmp_mrq_return(channel, -EINVAL, &zero, sizeof(zero));
		return;
	}

	entry->handler(mrq, channel, entry->data);

	spin_unlock(&bpmp->lock);
}