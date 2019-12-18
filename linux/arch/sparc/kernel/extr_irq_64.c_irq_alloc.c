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

/* Variables and functions */
 int __irq_alloc_descs (int,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  numa_node_id () ; 

unsigned int irq_alloc(unsigned int dev_handle, unsigned int dev_ino)
{
	int irq;

	irq = __irq_alloc_descs(-1, 1, 1, numa_node_id(), NULL, NULL);
	if (irq <= 0)
		goto out;

	return irq;
out:
	return 0;
}