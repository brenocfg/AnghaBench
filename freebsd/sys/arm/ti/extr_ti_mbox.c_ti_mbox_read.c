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
typedef  int /*<<< orphan*/  uint32_t ;
struct ti_mbox_softc {int dummy; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  TI_MBOX_MESSAGE (int) ; 
 struct ti_mbox_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int ti_mbox_reg_read (struct ti_mbox_softc*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
ti_mbox_read(device_t dev, int chan, uint32_t *data)
{
	struct ti_mbox_softc *sc;

	if (chan < 0 || chan > 7)
		return (EINVAL);
	sc = device_get_softc(dev);

	return (ti_mbox_reg_read(sc, TI_MBOX_MESSAGE(chan)));
}