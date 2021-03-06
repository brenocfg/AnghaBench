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
struct agp_memory {int dummy; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  AGP_FREE_MEMORY (int /*<<< orphan*/ ,struct agp_memory*) ; 

void agp_free_memory(device_t dev, void *handle)
{
	struct agp_memory *mem = (struct agp_memory *) handle;
	AGP_FREE_MEMORY(dev, mem);
}