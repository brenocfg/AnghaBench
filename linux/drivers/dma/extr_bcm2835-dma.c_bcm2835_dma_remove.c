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
struct bcm2835_dmadev {int /*<<< orphan*/  ddev; } ;

/* Variables and functions */
 int /*<<< orphan*/  bcm2835_dma_free (struct bcm2835_dmadev*) ; 
 int /*<<< orphan*/  dma_async_device_unregister (int /*<<< orphan*/ *) ; 
 struct bcm2835_dmadev* platform_get_drvdata (struct platform_device*) ; 

__attribute__((used)) static int bcm2835_dma_remove(struct platform_device *pdev)
{
	struct bcm2835_dmadev *od = platform_get_drvdata(pdev);

	dma_async_device_unregister(&od->ddev);
	bcm2835_dma_free(od);

	return 0;
}