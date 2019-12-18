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
struct opal_ipmi_softc {int /*<<< orphan*/  sc_msg; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  M_IPMI ; 
 struct opal_ipmi_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int ipmi_detach (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
opal_ipmi_detach(device_t dev)
{
	struct opal_ipmi_softc *sc;
	int err;

	sc = device_get_softc(dev);
	err = ipmi_detach(dev);
	if (err == 0)
		free(sc->sc_msg, M_IPMI);

	return (err);
}