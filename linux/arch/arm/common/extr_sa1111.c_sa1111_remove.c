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
struct sa1111 {int /*<<< orphan*/ * saved_state; } ;
struct platform_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  __sa1111_remove (struct sa1111*) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 struct sa1111* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int sa1111_remove(struct platform_device *pdev)
{
	struct sa1111 *sachip = platform_get_drvdata(pdev);

	if (sachip) {
#ifdef CONFIG_PM
		kfree(sachip->saved_state);
		sachip->saved_state = NULL;
#endif
		__sa1111_remove(sachip);
		platform_set_drvdata(pdev, NULL);
	}

	return 0;
}