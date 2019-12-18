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
struct zpci_dev {int /*<<< orphan*/  allocated_pages; } ;
struct seq_file {struct zpci_dev* private; } ;
typedef  int /*<<< orphan*/  atomic64_t ;

/* Variables and functions */
 int ARRAY_SIZE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic64_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * pci_sw_names ; 
 int /*<<< orphan*/  seq_printf (struct seq_file*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void pci_sw_counter_show(struct seq_file *m)
{
	struct zpci_dev *zdev = m->private;
	atomic64_t *counter = &zdev->allocated_pages;
	int i;

	for (i = 0; i < ARRAY_SIZE(pci_sw_names); i++, counter++)
		seq_printf(m, "%26s:\t%llu\n", pci_sw_names[i],
			   atomic64_read(counter));
}