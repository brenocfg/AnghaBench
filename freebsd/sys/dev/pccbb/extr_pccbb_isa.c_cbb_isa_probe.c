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
struct cbb_softc {int /*<<< orphan*/  bsh; int /*<<< orphan*/  bst; int /*<<< orphan*/ * exca; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int ENOENT ; 
 int ISA_PNP_PROBE (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int cbb_isa_activate (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cbb_isa_deactivate (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_get_parent (int /*<<< orphan*/ ) ; 
 struct cbb_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int exca_probe_slots (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pcic_ids ; 

__attribute__((used)) static int
cbb_isa_probe(device_t dev)
{
	int error;
	struct cbb_softc *sc = device_get_softc(dev);

	/* Check isapnp ids */
	error = ISA_PNP_PROBE(device_get_parent(dev), dev, pcic_ids);
	if (error != 0 && error != ENOENT)
		return (error);

	error = cbb_isa_activate(dev);
	if (error != 0)
		return (error);

	/* Check to make sure that we have actual hardware */
	error = exca_probe_slots(dev, &sc->exca[0], sc->bst, sc->bsh);
	cbb_isa_deactivate(dev);
	return (error);
}