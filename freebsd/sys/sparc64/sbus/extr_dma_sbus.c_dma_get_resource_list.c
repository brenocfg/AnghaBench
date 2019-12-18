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
struct resource_list {int dummy; } ;
struct dma_devinfo {struct resource_list ddi_rl; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 struct dma_devinfo* device_get_ivars (int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct resource_list *
dma_get_resource_list(device_t dev, device_t child)
{
	struct dma_devinfo *ddi;

	ddi = device_get_ivars(child);
	return (&ddi->ddi_rl);
}