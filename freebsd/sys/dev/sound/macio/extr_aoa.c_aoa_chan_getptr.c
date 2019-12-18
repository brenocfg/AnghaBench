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
typedef  int u_int32_t ;
struct aoa_dma {int slot; int blksz; int /*<<< orphan*/  running; } ;
typedef  int /*<<< orphan*/  kobj_t ;

/* Variables and functions */

__attribute__((used)) static u_int32_t
aoa_chan_getptr(kobj_t obj, void *data)
{
	struct aoa_dma 	 *dma = data;

	if (!dma->running)
		return (0);
	
	return (dma->slot * dma->blksz);
}