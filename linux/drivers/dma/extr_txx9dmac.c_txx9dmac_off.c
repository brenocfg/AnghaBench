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
struct txx9dmac_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MCR ; 
 int /*<<< orphan*/  dma_writel (struct txx9dmac_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void txx9dmac_off(struct txx9dmac_dev *ddev)
{
	dma_writel(ddev, MCR, 0);
}