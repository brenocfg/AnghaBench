#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int ref_count; void* maxsegsz; int /*<<< orphan*/  nsegments; void* maxsize; void* highaddr; void* lowaddr; scalar_t__ boundary; int /*<<< orphan*/ * impl; } ;
struct TYPE_6__ {int /*<<< orphan*/  owner; struct dmar_ctx* ctx; TYPE_2__ common; } ;
struct dmar_ctx {TYPE_3__ ctx_tag; TYPE_1__* domain; } ;
typedef  int /*<<< orphan*/  device_t ;
typedef  void* bus_addr_t ;
struct TYPE_4__ {int /*<<< orphan*/  end; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUS_SPACE_MAXADDR ; 
 int /*<<< orphan*/  BUS_SPACE_UNRESTRICTED ; 
 void* MIN (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_dma_dmar_impl ; 

__attribute__((used)) static void
ctx_tag_init(struct dmar_ctx *ctx, device_t dev)
{
	bus_addr_t maxaddr;

	maxaddr = MIN(ctx->domain->end, BUS_SPACE_MAXADDR);
	ctx->ctx_tag.common.ref_count = 1; /* Prevent free */
	ctx->ctx_tag.common.impl = &bus_dma_dmar_impl;
	ctx->ctx_tag.common.boundary = 0;
	ctx->ctx_tag.common.lowaddr = maxaddr;
	ctx->ctx_tag.common.highaddr = maxaddr;
	ctx->ctx_tag.common.maxsize = maxaddr;
	ctx->ctx_tag.common.nsegments = BUS_SPACE_UNRESTRICTED;
	ctx->ctx_tag.common.maxsegsz = maxaddr;
	ctx->ctx_tag.ctx = ctx;
	ctx->ctx_tag.owner = dev;
}