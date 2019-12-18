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
struct sram_bank_info {struct sram_bank_info* pool_name; int /*<<< orphan*/  sram_virt; int /*<<< orphan*/  gpool; int /*<<< orphan*/  node; } ;
struct platform_device {int dummy; } ;

/* Variables and functions */
 int ENODEV ; 
 int /*<<< orphan*/  gen_pool_destroy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iounmap (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct sram_bank_info*) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct sram_bank_info* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  sram_lock ; 

__attribute__((used)) static int sram_remove(struct platform_device *pdev)
{
	struct sram_bank_info *info;

	info = platform_get_drvdata(pdev);
	if (info == NULL)
		return -ENODEV;

	mutex_lock(&sram_lock);
	list_del(&info->node);
	mutex_unlock(&sram_lock);

	gen_pool_destroy(info->gpool);
	iounmap(info->sram_virt);
	kfree(info->pool_name);
	kfree(info);
	return 0;
}