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
struct resource {scalar_t__ start; scalar_t__ end; } ;
struct platform_device {int dummy; } ;
struct cns3xxx_i2c {int /*<<< orphan*/  base; int /*<<< orphan*/  adap; } ;

/* Variables and functions */
 int /*<<< orphan*/  CNS3xxx_I2C_DISABLE () ; 
 int /*<<< orphan*/  CNS3xxx_I2C_DISABLE_INTR () ; 
 int /*<<< orphan*/  IORESOURCE_IRQ ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 int /*<<< orphan*/  free_irq (scalar_t__,struct cns3xxx_i2c*) ; 
 int /*<<< orphan*/  i2c_del_adapter (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  iounmap (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct cns3xxx_i2c*) ; 
 struct cns3xxx_i2c* platform_get_drvdata (struct platform_device*) ; 
 struct resource* platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  release_mem_region (scalar_t__,scalar_t__) ; 

__attribute__((used)) static int cns3xxx_i2c_remove(struct platform_device *pdev)
{
	struct cns3xxx_i2c *i2c = platform_get_drvdata(pdev);
	struct resource *res;

	/* disable i2c logic */
	CNS3xxx_I2C_DISABLE_INTR();
	CNS3xxx_I2C_DISABLE();
	/* remove adapter & data */
	i2c_del_adapter(&i2c->adap);
	platform_set_drvdata(pdev, NULL);

	res = platform_get_resource(pdev, IORESOURCE_IRQ, 0);
	if (res)
		free_irq(res->start, i2c);

	iounmap(i2c->base);

	res = platform_get_resource(pdev, IORESOURCE_MEM, 0);
	if (res)
		release_mem_region(res->start, res->end - res->start + 1);

	kfree(i2c);

	return 0;
}