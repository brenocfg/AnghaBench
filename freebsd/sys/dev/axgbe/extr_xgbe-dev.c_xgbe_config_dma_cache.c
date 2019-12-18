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
struct xgbe_prv_data {int /*<<< orphan*/  axdomain; int /*<<< orphan*/  awcache; int /*<<< orphan*/  arcache; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_AXIARCR ; 
 int /*<<< orphan*/  DMA_AXIAWCR ; 
 int /*<<< orphan*/  DRC ; 
 int /*<<< orphan*/  DRD ; 
 int /*<<< orphan*/  DWC ; 
 int /*<<< orphan*/  DWD ; 
 int /*<<< orphan*/  RHC ; 
 int /*<<< orphan*/  RHD ; 
 int /*<<< orphan*/  RPC ; 
 int /*<<< orphan*/  RPD ; 
 int /*<<< orphan*/  TDC ; 
 int /*<<< orphan*/  TDD ; 
 int /*<<< orphan*/  TEC ; 
 int /*<<< orphan*/  TED ; 
 int /*<<< orphan*/  THC ; 
 int /*<<< orphan*/  THD ; 
 int /*<<< orphan*/  XGMAC_IOWRITE (struct xgbe_prv_data*,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  XGMAC_SET_BITS (unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void xgbe_config_dma_cache(struct xgbe_prv_data *pdata)
{
	unsigned int arcache, awcache;

	arcache = 0;
	XGMAC_SET_BITS(arcache, DMA_AXIARCR, DRC, pdata->arcache);
	XGMAC_SET_BITS(arcache, DMA_AXIARCR, DRD, pdata->axdomain);
	XGMAC_SET_BITS(arcache, DMA_AXIARCR, TEC, pdata->arcache);
	XGMAC_SET_BITS(arcache, DMA_AXIARCR, TED, pdata->axdomain);
	XGMAC_SET_BITS(arcache, DMA_AXIARCR, THC, pdata->arcache);
	XGMAC_SET_BITS(arcache, DMA_AXIARCR, THD, pdata->axdomain);
	XGMAC_IOWRITE(pdata, DMA_AXIARCR, arcache);

	awcache = 0;
	XGMAC_SET_BITS(awcache, DMA_AXIAWCR, DWC, pdata->awcache);
	XGMAC_SET_BITS(awcache, DMA_AXIAWCR, DWD, pdata->axdomain);
	XGMAC_SET_BITS(awcache, DMA_AXIAWCR, RPC, pdata->awcache);
	XGMAC_SET_BITS(awcache, DMA_AXIAWCR, RPD, pdata->axdomain);
	XGMAC_SET_BITS(awcache, DMA_AXIAWCR, RHC, pdata->awcache);
	XGMAC_SET_BITS(awcache, DMA_AXIAWCR, RHD, pdata->axdomain);
	XGMAC_SET_BITS(awcache, DMA_AXIAWCR, TDC, pdata->awcache);
	XGMAC_SET_BITS(awcache, DMA_AXIAWCR, TDD, pdata->axdomain);
	XGMAC_IOWRITE(pdata, DMA_AXIAWCR, awcache);
}