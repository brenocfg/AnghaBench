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
typedef  int /*<<< orphan*/  u32 ;
struct safexcel_desc_ring {int offset; void* base; void* read; void* base_end; void* write; int /*<<< orphan*/  base_dma; } ;
struct TYPE_2__ {int cd_offset; int rd_offset; } ;
struct safexcel_crypto_priv {int /*<<< orphan*/  dev; TYPE_1__ config; } ;

/* Variables and functions */
 int EIP197_DEFAULT_RING_SIZE ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 void* dmam_alloc_coherent (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

int safexcel_init_ring_descriptors(struct safexcel_crypto_priv *priv,
				   struct safexcel_desc_ring *cdr,
				   struct safexcel_desc_ring *rdr)
{
	cdr->offset = sizeof(u32) * priv->config.cd_offset;
	cdr->base = dmam_alloc_coherent(priv->dev,
					cdr->offset * EIP197_DEFAULT_RING_SIZE,
					&cdr->base_dma, GFP_KERNEL);
	if (!cdr->base)
		return -ENOMEM;
	cdr->write = cdr->base;
	cdr->base_end = cdr->base + cdr->offset * (EIP197_DEFAULT_RING_SIZE - 1);
	cdr->read = cdr->base;

	rdr->offset = sizeof(u32) * priv->config.rd_offset;
	rdr->base = dmam_alloc_coherent(priv->dev,
					rdr->offset * EIP197_DEFAULT_RING_SIZE,
					&rdr->base_dma, GFP_KERNEL);
	if (!rdr->base)
		return -ENOMEM;
	rdr->write = rdr->base;
	rdr->base_end = rdr->base + rdr->offset  * (EIP197_DEFAULT_RING_SIZE - 1);
	rdr->read = rdr->base;

	return 0;
}