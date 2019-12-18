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
struct xilly_mapping {size_t size; int direction; int /*<<< orphan*/  dma_addr; int /*<<< orphan*/  device; } ;
struct xilly_endpoint {int /*<<< orphan*/  dev; } ;
typedef  int /*<<< orphan*/  dma_addr_t ;

/* Variables and functions */
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int devm_add_action_or_reset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct xilly_mapping*) ; 
 int /*<<< orphan*/  dma_map_single (int /*<<< orphan*/ ,void*,size_t,int) ; 
 scalar_t__ dma_mapping_error (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct xilly_mapping*) ; 
 struct xilly_mapping* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xilly_of_unmap ; 

__attribute__((used)) static int xilly_map_single_of(struct xilly_endpoint *ep,
			       void *ptr,
			       size_t size,
			       int direction,
			       dma_addr_t *ret_dma_handle
	)
{
	dma_addr_t addr;
	struct xilly_mapping *this;

	this = kzalloc(sizeof(*this), GFP_KERNEL);
	if (!this)
		return -ENOMEM;

	addr = dma_map_single(ep->dev, ptr, size, direction);

	if (dma_mapping_error(ep->dev, addr)) {
		kfree(this);
		return -ENODEV;
	}

	this->device = ep->dev;
	this->dma_addr = addr;
	this->size = size;
	this->direction = direction;

	*ret_dma_handle = addr;

	return devm_add_action_or_reset(ep->dev, xilly_of_unmap, this);
}