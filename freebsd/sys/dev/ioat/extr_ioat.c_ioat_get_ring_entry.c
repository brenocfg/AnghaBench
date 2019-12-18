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
typedef  int uint32_t ;
struct ioat_softc {int ring_size_order; struct ioat_descriptor* ring; } ;
struct ioat_descriptor {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static struct ioat_descriptor *
ioat_get_ring_entry(struct ioat_softc *ioat, uint32_t index)
{

	return (&ioat->ring[index % (1 << ioat->ring_size_order)]);
}