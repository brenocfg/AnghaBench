#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct s3c24xx_dma_platdata {struct s3c24xx_dma_channel* channels; } ;
struct s3c24xx_dma_phy {int id; } ;
struct s3c24xx_dma_engine {TYPE_1__* sdata; struct s3c24xx_dma_platdata* pdata; } ;
struct s3c24xx_dma_channel {int chansel; } ;
struct s3c24xx_dma_chan {size_t id; int /*<<< orphan*/  slave; struct s3c24xx_dma_engine* host; } ;
struct TYPE_2__ {scalar_t__ has_reqsel; } ;

/* Variables and functions */
 int S3C24XX_CHANSEL_VALID ; 
 int S3C24XX_CHANSEL_WIDTH ; 

__attribute__((used)) static bool s3c24xx_dma_phy_valid(struct s3c24xx_dma_chan *s3cchan,
				  struct s3c24xx_dma_phy *phy)
{
	struct s3c24xx_dma_engine *s3cdma = s3cchan->host;
	const struct s3c24xx_dma_platdata *pdata = s3cdma->pdata;
	struct s3c24xx_dma_channel *cdata = &pdata->channels[s3cchan->id];
	int phyvalid;

	/* every phy is valid for memcopy channels */
	if (!s3cchan->slave)
		return true;

	/* On newer variants all phys can be used for all virtual channels */
	if (s3cdma->sdata->has_reqsel)
		return true;

	phyvalid = (cdata->chansel >> (phy->id * S3C24XX_CHANSEL_WIDTH));
	return (phyvalid & S3C24XX_CHANSEL_VALID) ? true : false;
}