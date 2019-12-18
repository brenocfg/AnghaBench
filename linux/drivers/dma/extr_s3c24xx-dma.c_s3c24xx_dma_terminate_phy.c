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
struct s3c24xx_dma_phy {scalar_t__ base; } ;

/* Variables and functions */
 scalar_t__ S3C24XX_DMASKTRIG ; 
 int /*<<< orphan*/  S3C24XX_DMASKTRIG_STOP ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void s3c24xx_dma_terminate_phy(struct s3c24xx_dma_phy *phy)
{
	writel(S3C24XX_DMASKTRIG_STOP, phy->base + S3C24XX_DMASKTRIG);
}