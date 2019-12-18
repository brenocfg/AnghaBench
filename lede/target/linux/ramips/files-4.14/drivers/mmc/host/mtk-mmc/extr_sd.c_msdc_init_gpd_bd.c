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
typedef  scalar_t__ u32 ;
struct msdc_host {int dummy; } ;
struct msdc_dma {scalar_t__ bd_addr; scalar_t__ gpd_addr; struct gpd* bd; struct gpd* gpd; } ;
struct gpd {int bdp; void* next; void* ptr; } ;
struct bd {int bdp; void* next; void* ptr; } ;

/* Variables and functions */
 int MAX_BD_NUM ; 
 int /*<<< orphan*/  memset (struct gpd*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void msdc_init_gpd_bd(struct msdc_host *host, struct msdc_dma *dma)
{
	struct gpd *gpd = dma->gpd;
	struct bd  *bd  = dma->bd;
	int i;

	/* we just support one gpd, but gpd->next must be set for desc
	 * DMA. That's why we alloc 2 gpd structurs.
	 */

	memset(gpd, 0, sizeof(struct gpd) * 2);

	gpd->bdp  = 1;   /* hwo, cs, bd pointer */
	gpd->ptr = (void *)dma->bd_addr; /* physical address */
	gpd->next = (void *)((u32)dma->gpd_addr + sizeof(struct gpd));

	memset(bd, 0, sizeof(struct bd) * MAX_BD_NUM);
	for (i = 0; i < (MAX_BD_NUM - 1); i++)
		bd[i].next = (void *)(dma->bd_addr + sizeof(*bd) * (i + 1));
}