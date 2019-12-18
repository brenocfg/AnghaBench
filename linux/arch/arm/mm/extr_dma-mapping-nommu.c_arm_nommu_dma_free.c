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
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  dma_addr_t ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON_ONCE (int) ; 
 int dma_release_from_global_coherent (int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  get_order (size_t) ; 

__attribute__((used)) static void arm_nommu_dma_free(struct device *dev, size_t size,
			       void *cpu_addr, dma_addr_t dma_addr,
			       unsigned long attrs)
{
	int ret = dma_release_from_global_coherent(get_order(size), cpu_addr);

	WARN_ON_ONCE(ret == 0);
}