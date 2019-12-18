#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct octebus_softc {int /*<<< orphan*/  sc_dev; int /*<<< orphan*/ * sc_rgmii_irq; } ;
struct ifnet {scalar_t__ if_softc; } ;
struct TYPE_5__ {int phy_dupx; int phy_link; int phy_spd; } ;
struct TYPE_6__ {int /*<<< orphan*/  u64; TYPE_1__ s; } ;
typedef  TYPE_2__ cvmx_gmxx_rxx_int_en_t ;
struct TYPE_7__ {scalar_t__ imode; scalar_t__ port; int /*<<< orphan*/  poll; int /*<<< orphan*/  dev; int /*<<< orphan*/  (* stop ) (struct ifnet*) ;int /*<<< orphan*/  open; } ;
typedef  TYPE_3__ cvm_oct_private_t ;
struct TYPE_8__ {scalar_t__ board_type; } ;

/* Variables and functions */
 scalar_t__ CVMX_BOARD_TYPE_SIM ; 
 int /*<<< orphan*/  CVMX_GMXX_RXX_INT_EN (int,int) ; 
 scalar_t__ CVMX_HELPER_INTERFACE_MODE_GMII ; 
 scalar_t__ CVMX_HELPER_INTERFACE_MODE_RGMII ; 
 int ENXIO ; 
 int INDEX (scalar_t__) ; 
 int INTERFACE (scalar_t__) ; 
 int INTR_MPSAFE ; 
 int INTR_TYPE_NET ; 
 int /*<<< orphan*/  OCTEON_IRQ_RML ; 
 int /*<<< orphan*/  RF_ACTIVE ; 
 int /*<<< orphan*/  SYS_RES_IRQ ; 
 int /*<<< orphan*/ * bus_alloc_resource (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int bus_setup_intr (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,scalar_t__*,int /*<<< orphan*/ *) ; 
 scalar_t__ cvm_oct_common_init (struct ifnet*) ; 
 int /*<<< orphan*/  cvm_oct_common_open ; 
 int /*<<< orphan*/  cvm_oct_common_stop (struct ifnet*) ; 
 int /*<<< orphan*/  cvm_oct_rgmii_poll ; 
 int /*<<< orphan*/  cvm_oct_rgmii_rml_interrupt ; 
 int /*<<< orphan*/  cvmx_read_csr (int /*<<< orphan*/ ) ; 
 TYPE_4__* cvmx_sysinfo_get () ; 
 int /*<<< orphan*/  cvmx_write_csr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_get_parent (int /*<<< orphan*/ ) ; 
 struct octebus_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ number_rgmii_ports ; 
 int /*<<< orphan*/  stub1 (struct ifnet*) ; 

int cvm_oct_rgmii_init(struct ifnet *ifp)
{
	struct octebus_softc *sc;
	cvm_oct_private_t *priv = (cvm_oct_private_t *)ifp->if_softc;
	int error;
	int rid;

	if (cvm_oct_common_init(ifp) != 0)
	    return ENXIO;

	priv->open = cvm_oct_common_open;
	priv->stop = cvm_oct_common_stop;
	priv->stop(ifp);

	/* Due to GMX errata in CN3XXX series chips, it is necessary to take the
	   link down immediately whne the PHY changes state. In order to do this
	   we call the poll function every time the RGMII inband status changes.
	   This may cause problems if the PHY doesn't implement inband status
	   properly */
	if (number_rgmii_ports == 0) {
		sc = device_get_softc(device_get_parent(priv->dev));

		rid = 0;
		sc->sc_rgmii_irq = bus_alloc_resource(sc->sc_dev, SYS_RES_IRQ,
						      &rid, OCTEON_IRQ_RML,
						      OCTEON_IRQ_RML, 1,
						      RF_ACTIVE);
		if (sc->sc_rgmii_irq == NULL) {
			device_printf(sc->sc_dev, "could not allocate RGMII irq");
			return ENXIO;
		}

		error = bus_setup_intr(sc->sc_dev, sc->sc_rgmii_irq,
				       INTR_TYPE_NET | INTR_MPSAFE,
				       cvm_oct_rgmii_rml_interrupt, NULL,
				       &number_rgmii_ports, NULL);
		if (error != 0) {
			device_printf(sc->sc_dev, "could not setup RGMII irq");
			return error;
		}
	}
	number_rgmii_ports++;

	/* Only true RGMII ports need to be polled. In GMII mode, port 0 is really
	   a RGMII port */
	if (((priv->imode == CVMX_HELPER_INTERFACE_MODE_GMII) && (priv->port == 0)) ||
	    (priv->imode == CVMX_HELPER_INTERFACE_MODE_RGMII)) {

		if (cvmx_sysinfo_get()->board_type != CVMX_BOARD_TYPE_SIM) {

			cvmx_gmxx_rxx_int_en_t gmx_rx_int_en;
			int interface = INTERFACE(priv->port);
			int index = INDEX(priv->port);

			/* Enable interrupts on inband status changes for this port */
			gmx_rx_int_en.u64 = cvmx_read_csr(CVMX_GMXX_RXX_INT_EN(index, interface));
			gmx_rx_int_en.s.phy_dupx = 1;
			gmx_rx_int_en.s.phy_link = 1;
			gmx_rx_int_en.s.phy_spd = 1;
			cvmx_write_csr(CVMX_GMXX_RXX_INT_EN(index, interface), gmx_rx_int_en.u64);
			priv->poll = cvm_oct_rgmii_poll;
		}
	}

	return 0;
}