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
struct pxad_device {int /*<<< orphan*/  slave; } ;
struct platform_device {int dummy; } ;

/* Variables and functions */
 struct pxad_device* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  pxad_cleanup_debugfs (struct pxad_device*) ; 
 int /*<<< orphan*/  pxad_free_channels (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int pxad_remove(struct platform_device *op)
{
	struct pxad_device *pdev = platform_get_drvdata(op);

	pxad_cleanup_debugfs(pdev);
	pxad_free_channels(&pdev->slave);
	return 0;
}