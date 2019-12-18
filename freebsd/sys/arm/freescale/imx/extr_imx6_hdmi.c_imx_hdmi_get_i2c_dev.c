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
struct imx_hdmi_softc {scalar_t__ i2c_xref; } ;
typedef  int /*<<< orphan*/ * device_t ;

/* Variables and functions */
 int /*<<< orphan*/ * OF_device_from_xref (scalar_t__) ; 
 struct imx_hdmi_softc* device_get_softc (int /*<<< orphan*/ *) ; 

__attribute__((used)) static device_t
imx_hdmi_get_i2c_dev(device_t dev)
{
	struct imx_hdmi_softc *sc;

	sc = device_get_softc(dev);

	if (sc->i2c_xref == 0)
		return (NULL);

	return (OF_device_from_xref(sc->i2c_xref));
}