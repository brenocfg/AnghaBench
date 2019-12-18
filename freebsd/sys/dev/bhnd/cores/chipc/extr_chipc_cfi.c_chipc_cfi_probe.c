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
struct cfi_softc {scalar_t__ sc_width; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int cfi_probe (int /*<<< orphan*/ ) ; 
 struct cfi_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_set_desc (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int
chipc_cfi_probe(device_t dev)
{
	struct cfi_softc	*sc;
	int			error;

	sc = device_get_softc(dev);

	sc->sc_width = 0;
	if ((error = cfi_probe(dev)) > 0)
		return (error);

	device_set_desc(dev, "Broadcom ChipCommon CFI");
	return (error);
}