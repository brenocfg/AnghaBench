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
struct scc_softc {int /*<<< orphan*/ * sc_class; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int BUS_READ_IVAR (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,uintptr_t*) ; 
 int ENXIO ; 
 uintptr_t QUICC_DEVTYPE_SCC ; 
 int /*<<< orphan*/  QUICC_IVAR_BRGCLK ; 
 int /*<<< orphan*/  QUICC_IVAR_DEVTYPE ; 
 int /*<<< orphan*/  device_get_parent (int /*<<< orphan*/ ) ; 
 struct scc_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_set_desc (int /*<<< orphan*/ ,char*) ; 
 int scc_bfe_probe (int /*<<< orphan*/ ,int /*<<< orphan*/ ,uintptr_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  scc_quicc_class ; 

__attribute__((used)) static int
scc_quicc_probe(device_t dev)
{
	device_t parent;
	struct scc_softc *sc;
	uintptr_t devtype, rclk;
	int error;

	parent = device_get_parent(dev);

	error = BUS_READ_IVAR(parent, dev, QUICC_IVAR_DEVTYPE, &devtype);
	if (error)
		return (error);
	if (devtype != QUICC_DEVTYPE_SCC)
		return (ENXIO);

	device_set_desc(dev, "QUICC quad channel SCC");

	sc = device_get_softc(dev);
	sc->sc_class = &scc_quicc_class;
	if (BUS_READ_IVAR(parent, dev, QUICC_IVAR_BRGCLK, &rclk))
		rclk = 0;
	return (scc_bfe_probe(dev, 0, rclk, 0));
}