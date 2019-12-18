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
typedef  int /*<<< orphan*/  uint64_t ;
struct xlp_rsa_softc {scalar_t__ sc_cid; int rsaecc_vc_start; int rsaecc_vc_end; int /*<<< orphan*/  sc_dev; } ;
struct xlp_rsa_session {int dummy; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  CRK_MOD_EXP ; 
 int /*<<< orphan*/  CRYPTOCAP_F_HARDWARE ; 
 int /*<<< orphan*/  DFS_DEVICE_RSA ; 
 int ENXIO ; 
 scalar_t__ PCI_DEVICE_ID_NLM_RSA ; 
 scalar_t__ bootverbose ; 
 scalar_t__ crypto_get_driverid (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 scalar_t__ crypto_kregister (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct xlp_rsa_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  device_set_desc (int /*<<< orphan*/ ,char*) ; 
 int nlm_get_device_node (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nlm_get_rsa_pcibase (int) ; 
 int nlm_qidstart (int /*<<< orphan*/ ) ; 
 int nlm_qnum (int /*<<< orphan*/ ) ; 
 int nlm_set_device_frequency (int,int /*<<< orphan*/ ,int) ; 
 scalar_t__ pci_get_device (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_get_slot (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*) ; 
 scalar_t__ xlp_rsa_init (struct xlp_rsa_softc*,int) ; 

__attribute__((used)) static int
xlp_rsa_attach(device_t dev)
{
	struct xlp_rsa_softc *sc = device_get_softc(dev);
	uint64_t base;
	int qstart, qnum;
	int freq, node;

	sc->sc_dev = dev;

	node = nlm_get_device_node(pci_get_slot(dev));
	freq = nlm_set_device_frequency(node, DFS_DEVICE_RSA, 250);
	if (bootverbose)
		device_printf(dev, "RSA Freq: %dMHz\n", freq);
	if (pci_get_device(dev) == PCI_DEVICE_ID_NLM_RSA) {
		device_set_desc(dev, "XLP RSA/ECC Accelerator");
		sc->sc_cid = crypto_get_driverid(dev,
		    sizeof(struct xlp_rsa_session), CRYPTOCAP_F_HARDWARE);
		if (sc->sc_cid < 0) {
			printf("xlp_rsaecc-err:couldn't get the driver id\n");
			goto error_exit;
		}
		if (crypto_kregister(sc->sc_cid, CRK_MOD_EXP, 0) != 0)
			goto error_exit;

		base = nlm_get_rsa_pcibase(node);
		qstart = nlm_qidstart(base);
		qnum = nlm_qnum(base);
		sc->rsaecc_vc_start = qstart;
		sc->rsaecc_vc_end = qstart + qnum - 1;
	}
	if (xlp_rsa_init(sc, node) != 0)
		goto error_exit;
	device_printf(dev, "RSA Initialization complete!\n");
	return (0);

error_exit:
	return (ENXIO);
}