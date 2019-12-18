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
 int __afu_port_disable (struct platform_device*) ; 
 int /*<<< orphan*/  __afu_port_enable (struct platform_device*) ; 

__attribute__((used)) static int __port_reset(struct platform_device *pdev)
{
	int ret;

	ret = __afu_port_disable(pdev);
	if (!ret)
		__afu_port_enable(pdev);

	return ret;
}