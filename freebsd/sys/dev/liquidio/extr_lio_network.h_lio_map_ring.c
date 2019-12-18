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
typedef  scalar_t__ vm_paddr_t ;
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int /*<<< orphan*/  uint32_t ;
struct mbuf {int /*<<< orphan*/  m_data; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 scalar_t__ vtophys (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline uint64_t
lio_map_ring(device_t dev, void *buf, uint32_t size)
{
	vm_paddr_t	dma_addr;

	dma_addr = vtophys(((struct mbuf *)buf)->m_data);
	return ((uint64_t)dma_addr);
}