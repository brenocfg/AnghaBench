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
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEV_DAX_BUS ; 
 int PTR_ERR_OR_ZERO (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __dax_pmem_probe (struct device*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int dax_pmem_probe(struct device *dev)
{
	return PTR_ERR_OR_ZERO(__dax_pmem_probe(dev, DEV_DAX_BUS));
}