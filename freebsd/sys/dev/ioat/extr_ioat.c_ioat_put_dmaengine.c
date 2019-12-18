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
struct ioat_softc {int /*<<< orphan*/  submit_lock; } ;
typedef  int /*<<< orphan*/  bus_dmaengine_t ;

/* Variables and functions */
 int /*<<< orphan*/  ioat_put (struct ioat_softc*) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 struct ioat_softc* to_ioat_softc (int /*<<< orphan*/ ) ; 

void
ioat_put_dmaengine(bus_dmaengine_t dmaengine)
{
	struct ioat_softc *ioat;

	ioat = to_ioat_softc(dmaengine);
	mtx_lock(&ioat->submit_lock);
	ioat_put(ioat);
	mtx_unlock(&ioat->submit_lock);
}