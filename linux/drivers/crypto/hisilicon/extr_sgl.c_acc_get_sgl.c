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
typedef  int u32 ;
struct hisi_acc_sgl_pool {int count; int sgl_size; scalar_t__ sgl; scalar_t__ sgl_dma; } ;
typedef  void hisi_acc_hw_sgl ;
typedef  scalar_t__ dma_addr_t ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 void* ERR_PTR (int /*<<< orphan*/ ) ; 

struct hisi_acc_hw_sgl *acc_get_sgl(struct hisi_acc_sgl_pool *pool, u32 index,
				    dma_addr_t *hw_sgl_dma)
{
	if (!pool || !hw_sgl_dma || index >= pool->count || !pool->sgl)
		return ERR_PTR(-EINVAL);

	*hw_sgl_dma = pool->sgl_dma + pool->sgl_size * index;
	return (void *)pool->sgl + pool->sgl_size * index;
}