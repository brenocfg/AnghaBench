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
typedef  scalar_t__ uint16_t ;
struct ioat_softc {scalar_t__ intrdelay_max; int cached_intrdelay; int /*<<< orphan*/  intrdelay_supported; } ;
typedef  int /*<<< orphan*/  bus_dmaengine_t ;

/* Variables and functions */
 int ENODEV ; 
 int ERANGE ; 
 int /*<<< orphan*/  IOAT_INTRDELAY_OFFSET ; 
 int IOAT_INTRDELAY_US_MASK ; 
 int ioat_read_2 (struct ioat_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ioat_write_2 (struct ioat_softc*,int /*<<< orphan*/ ,scalar_t__) ; 
 struct ioat_softc* to_ioat_softc (int /*<<< orphan*/ ) ; 

int
ioat_set_interrupt_coalesce(bus_dmaengine_t dmaengine, uint16_t delay)
{
	struct ioat_softc *ioat;

	ioat = to_ioat_softc(dmaengine);
	if (!ioat->intrdelay_supported)
		return (ENODEV);
	if (delay > ioat->intrdelay_max)
		return (ERANGE);

	ioat_write_2(ioat, IOAT_INTRDELAY_OFFSET, delay);
	ioat->cached_intrdelay =
	    ioat_read_2(ioat, IOAT_INTRDELAY_OFFSET) & IOAT_INTRDELAY_US_MASK;
	return (0);
}