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
struct seq_file {int dummy; } ;
struct kvmppc_passthru_irqmap {int n_mapped; TYPE_1__* mapped; } ;
struct TYPE_2__ {int /*<<< orphan*/  v_hwirq; int /*<<< orphan*/  r_hwirq; } ;

/* Variables and functions */
 int /*<<< orphan*/  seq_printf (struct seq_file*,char*,int,...) ; 

__attribute__((used)) static void xics_debugfs_irqmap(struct seq_file *m,
				struct kvmppc_passthru_irqmap *pimap)
{
	int i;

	if (!pimap)
		return;
	seq_printf(m, "========\nPIRQ mappings: %d maps\n===========\n",
				pimap->n_mapped);
	for (i = 0; i < pimap->n_mapped; i++)  {
		seq_printf(m, "r_hwirq=%x, v_hwirq=%x\n",
			pimap->mapped[i].r_hwirq, pimap->mapped[i].v_hwirq);
	}
}