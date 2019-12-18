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
struct apei_resources {int /*<<< orphan*/  ioport; int /*<<< orphan*/  iomem; } ;

/* Variables and functions */
 int apei_res_add (int /*<<< orphan*/ *,unsigned long,unsigned long) ; 

int apei_resources_add(struct apei_resources *resources,
		       unsigned long start, unsigned long size,
		       bool iomem)
{
	if (iomem)
		return apei_res_add(&resources->iomem, start, size);
	else
		return apei_res_add(&resources->ioport, start, size);
}