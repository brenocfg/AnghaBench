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
typedef  union ioat_hw_descriptor {int dummy; } ioat_hw_descriptor ;
typedef  int uint32_t ;
struct ioat_softc {int ring_size_order; union ioat_hw_descriptor* hw_desc_ring; } ;

/* Variables and functions */

__attribute__((used)) static union ioat_hw_descriptor *
ioat_get_descriptor(struct ioat_softc *ioat, uint32_t index)
{

	return (&ioat->hw_desc_ring[index % (1 << ioat->ring_size_order)]);
}