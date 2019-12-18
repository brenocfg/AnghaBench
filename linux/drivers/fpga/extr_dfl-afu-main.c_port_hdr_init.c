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
struct dfl_feature {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  port_reset (struct platform_device*) ; 

__attribute__((used)) static int port_hdr_init(struct platform_device *pdev,
			 struct dfl_feature *feature)
{
	port_reset(pdev);

	return 0;
}