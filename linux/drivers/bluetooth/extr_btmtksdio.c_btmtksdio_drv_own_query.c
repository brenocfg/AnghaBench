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
typedef  int /*<<< orphan*/  u32 ;
struct btmtksdio_dev {int /*<<< orphan*/  func; } ;

/* Variables and functions */
 int /*<<< orphan*/  MTK_REG_CHLPCR ; 
 int /*<<< orphan*/  sdio_readl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static u32 btmtksdio_drv_own_query(struct btmtksdio_dev *bdev)
{
	return sdio_readl(bdev->func, MTK_REG_CHLPCR, NULL);
}