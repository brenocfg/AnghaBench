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
struct platform_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  handle_simple_irq ; 
 unsigned int leon_build_device_irq (unsigned int,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static unsigned int _leon_build_device_irq(struct platform_device *op,
					   unsigned int real_irq)
{
	return leon_build_device_irq(real_irq, handle_simple_irq, "edge", 0);
}