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
typedef  int /*<<< orphan*/  u64 ;
struct device {int dummy; } ;

/* Variables and functions */
 int __dma_supported (struct device*,int /*<<< orphan*/ ,int) ; 

int arm_dma_supported(struct device *dev, u64 mask)
{
	return __dma_supported(dev, mask, false);
}