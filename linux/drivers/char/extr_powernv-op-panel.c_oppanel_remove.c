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
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  misc_deregister (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  oppanel_data ; 
 int /*<<< orphan*/  oppanel_dev ; 
 int /*<<< orphan*/  oppanel_lines ; 

__attribute__((used)) static int oppanel_remove(struct platform_device *pdev)
{
	misc_deregister(&oppanel_dev);
	kfree(oppanel_lines);
	kfree(oppanel_data);
	return 0;
}