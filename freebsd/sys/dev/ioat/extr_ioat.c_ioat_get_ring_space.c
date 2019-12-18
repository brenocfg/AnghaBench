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
struct ioat_softc {int ring_size_order; } ;

/* Variables and functions */
 int ioat_get_active (struct ioat_softc*) ; 

__attribute__((used)) static inline uint32_t
ioat_get_ring_space(struct ioat_softc *ioat)
{

	return ((1 << ioat->ring_size_order) - ioat_get_active(ioat) - 1);
}