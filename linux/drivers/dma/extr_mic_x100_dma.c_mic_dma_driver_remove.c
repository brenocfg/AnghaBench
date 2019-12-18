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
struct mic_dma_device {int /*<<< orphan*/  dbg_dir; } ;
struct mbus_device {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  debugfs_remove_recursive (int /*<<< orphan*/ ) ; 
 struct mic_dma_device* dev_get_drvdata (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mic_dma_dev_unreg (struct mic_dma_device*) ; 

__attribute__((used)) static void mic_dma_driver_remove(struct mbus_device *mbdev)
{
	struct mic_dma_device *mic_dma_dev;

	mic_dma_dev = dev_get_drvdata(&mbdev->dev);
	debugfs_remove_recursive(mic_dma_dev->dbg_dir);
	mic_dma_dev_unreg(mic_dma_dev);
}