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
typedef  size_t vm_paddr_t ;
struct vmctx {size_t lowmem; void* baseaddr; int highmem; } ;

/* Variables and functions */
 int GB ; 

void *
vm_map_gpa(struct vmctx *ctx, vm_paddr_t gaddr, size_t len)
{

	if (ctx->lowmem > 0) {
		if (gaddr < ctx->lowmem && len <= ctx->lowmem &&
		    gaddr + len <= ctx->lowmem)
			return (ctx->baseaddr + gaddr);
	}

	if (ctx->highmem > 0) {
                if (gaddr >= 4*GB) {
			if (gaddr < 4*GB + ctx->highmem &&
			    len <= ctx->highmem &&
			    gaddr + len <= 4*GB + ctx->highmem)
				return (ctx->baseaddr + gaddr);
		}
	}

	return (NULL);
}