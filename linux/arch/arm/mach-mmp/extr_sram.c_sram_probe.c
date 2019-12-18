#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct sram_platdata {int /*<<< orphan*/  granularity; int /*<<< orphan*/  pool_name; } ;
struct sram_bank_info {struct sram_bank_info* pool_name; scalar_t__ sram_virt; int /*<<< orphan*/  gpool; int /*<<< orphan*/  node; scalar_t__ sram_size; scalar_t__ sram_phys; int /*<<< orphan*/  granularity; } ;
struct resource {scalar_t__ start; } ;
struct TYPE_3__ {struct sram_platdata* platform_data; } ;
struct platform_device {TYPE_1__ dev; } ;
typedef  scalar_t__ phys_addr_t ;

/* Variables and functions */
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 int /*<<< orphan*/  dev_err (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  dev_info (TYPE_1__*,char*) ; 
 int gen_pool_add_virt (int /*<<< orphan*/ ,unsigned long,scalar_t__,scalar_t__,int) ; 
 int /*<<< orphan*/  gen_pool_create (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  gen_pool_destroy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ilog2 (int /*<<< orphan*/ ) ; 
 scalar_t__ ioremap (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  iounmap (scalar_t__) ; 
 int /*<<< orphan*/  kfree (struct sram_bank_info*) ; 
 struct sram_bank_info* kstrdup (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct sram_bank_info* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct resource* platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct sram_bank_info*) ; 
 scalar_t__ resource_size (struct resource*) ; 
 int /*<<< orphan*/  sram_bank_list ; 
 int /*<<< orphan*/  sram_lock ; 

__attribute__((used)) static int sram_probe(struct platform_device *pdev)
{
	struct sram_platdata *pdata = pdev->dev.platform_data;
	struct sram_bank_info *info;
	struct resource *res;
	int ret = 0;

	if (!pdata || !pdata->pool_name)
		return -ENODEV;

	info = kzalloc(sizeof(*info), GFP_KERNEL);
	if (!info)
		return -ENOMEM;

	res = platform_get_resource(pdev, IORESOURCE_MEM, 0);
	if (res == NULL) {
		dev_err(&pdev->dev, "no memory resource defined\n");
		ret = -ENODEV;
		goto out;
	}

	if (!resource_size(res))
		return 0;

	info->sram_phys   = (phys_addr_t)res->start;
	info->sram_size   = resource_size(res);
	info->sram_virt   = ioremap(info->sram_phys, info->sram_size);
	info->pool_name	  = kstrdup(pdata->pool_name, GFP_KERNEL);
	info->granularity = pdata->granularity;

	info->gpool = gen_pool_create(ilog2(info->granularity), -1);
	if (!info->gpool) {
		dev_err(&pdev->dev, "create pool failed\n");
		ret = -ENOMEM;
		goto create_pool_err;
	}

	ret = gen_pool_add_virt(info->gpool, (unsigned long)info->sram_virt,
				info->sram_phys, info->sram_size, -1);
	if (ret < 0) {
		dev_err(&pdev->dev, "add new chunk failed\n");
		ret = -ENOMEM;
		goto add_chunk_err;
	}

	mutex_lock(&sram_lock);
	list_add(&info->node, &sram_bank_list);
	mutex_unlock(&sram_lock);

	platform_set_drvdata(pdev, info);

	dev_info(&pdev->dev, "initialized\n");
	return 0;

add_chunk_err:
	gen_pool_destroy(info->gpool);
create_pool_err:
	iounmap(info->sram_virt);
	kfree(info->pool_name);
out:
	kfree(info);
	return ret;
}