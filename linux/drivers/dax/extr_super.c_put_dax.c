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
struct dax_device {int /*<<< orphan*/  inode; } ;

/* Variables and functions */
 int /*<<< orphan*/  iput (int /*<<< orphan*/ *) ; 

void put_dax(struct dax_device *dax_dev)
{
	if (!dax_dev)
		return;
	iput(&dax_dev->inode);
}