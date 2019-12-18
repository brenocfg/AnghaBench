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
struct seq_file {struct hidma_dev* private; } ;
struct hidma_dev {TYPE_1__* evca_resource; int /*<<< orphan*/  dev_evca; TYPE_1__* trca_resource; int /*<<< orphan*/  dev_trca; int /*<<< orphan*/ * nr_descriptors; } ;
typedef  int /*<<< orphan*/  resource_size_t ;
struct TYPE_2__ {int /*<<< orphan*/  start; } ;

/* Variables and functions */
 int /*<<< orphan*/  resource_size (TYPE_1__*) ; 
 int /*<<< orphan*/  seq_printf (struct seq_file*,char*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int hidma_dma_show(struct seq_file *s, void *unused)
{
	struct hidma_dev *dmadev = s->private;
	resource_size_t sz;

	seq_printf(s, "nr_descriptors=%d\n", dmadev->nr_descriptors);
	seq_printf(s, "dev_trca=%p\n", &dmadev->dev_trca);
	seq_printf(s, "dev_trca_phys=%pa\n", &dmadev->trca_resource->start);
	sz = resource_size(dmadev->trca_resource);
	seq_printf(s, "dev_trca_size=%pa\n", &sz);
	seq_printf(s, "dev_evca=%p\n", &dmadev->dev_evca);
	seq_printf(s, "dev_evca_phys=%pa\n", &dmadev->evca_resource->start);
	sz = resource_size(dmadev->evca_resource);
	seq_printf(s, "dev_evca_size=%pa\n", &sz);
	return 0;
}