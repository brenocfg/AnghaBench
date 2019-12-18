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
struct amdvi_softc {int dummy; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  amdvi_teardown_hw (struct amdvi_softc*) ; 
 struct amdvi_softc* device_get_softc (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
ivhd_detach(device_t dev)
{
	struct amdvi_softc *softc;

	softc = device_get_softc(dev);

	amdvi_teardown_hw(softc);

	/*
	 * XXX: delete the device.
	 * don't allow detach, return EBUSY.
	 */
	return (0);
}