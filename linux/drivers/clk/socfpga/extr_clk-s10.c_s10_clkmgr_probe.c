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
 int s10_clkmgr_init (struct platform_device*) ; 

__attribute__((used)) static int s10_clkmgr_probe(struct platform_device *pdev)
{
	return	s10_clkmgr_init(pdev);
}