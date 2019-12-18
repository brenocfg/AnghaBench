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
struct ssp_device {int /*<<< orphan*/  node; } ;
struct platform_device {int dummy; } ;

/* Variables and functions */
 int ENODEV ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct ssp_device* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  ssp_lock ; 

__attribute__((used)) static int pxa_ssp_remove(struct platform_device *pdev)
{
	struct ssp_device *ssp;

	ssp = platform_get_drvdata(pdev);
	if (ssp == NULL)
		return -ENODEV;

	mutex_lock(&ssp_lock);
	list_del(&ssp->node);
	mutex_unlock(&ssp_lock);

	return 0;
}