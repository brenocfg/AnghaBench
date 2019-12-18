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
struct ioat_softc {int dummy; } ;
typedef  int /*<<< orphan*/  bus_dmaengine_t ;

/* Variables and functions */
 int /*<<< orphan*/  ioat_acquire (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ioat_release (int /*<<< orphan*/ ) ; 
 int ioat_reserve_space (struct ioat_softc*,unsigned int,int) ; 
 struct ioat_softc* to_ioat_softc (int /*<<< orphan*/ ) ; 

int
ioat_acquire_reserve(bus_dmaengine_t dmaengine, unsigned n, int mflags)
{
	struct ioat_softc *ioat;
	int error;

	ioat = to_ioat_softc(dmaengine);
	ioat_acquire(dmaengine);

	error = ioat_reserve_space(ioat, n, mflags);
	if (error != 0)
		ioat_release(dmaengine);
	return (error);
}