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
typedef  int /*<<< orphan*/  u64 ;
struct resource {int dummy; } ;
struct platform_device_info {char const* name; int id; unsigned int num_res; void const* data; size_t size_data; int /*<<< orphan*/  dma_mask; struct resource const* res; } ;
struct platform_device {int dummy; } ;

/* Variables and functions */
 struct platform_device* platform_device_register_full (struct platform_device_info*) ; 

__attribute__((used)) static inline struct platform_device *imx_add_platform_device_dmamask(
		const char *name, int id,
		const struct resource *res, unsigned int num_resources,
		const void *data, size_t size_data, u64 dmamask)
{
	struct platform_device_info pdevinfo = {
		.name = name,
		.id = id,
		.res = res,
		.num_res = num_resources,
		.data = data,
		.size_data = size_data,
		.dma_mask = dmamask,
	};
	return platform_device_register_full(&pdevinfo);
}