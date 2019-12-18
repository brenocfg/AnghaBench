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
struct xlp_sec_softc {scalar_t__ sc_cid; int sec_vc_start; int sec_vc_end; int /*<<< orphan*/  sc_dev; } ;
struct xlp_sec_session {int dummy; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  CRYPTOCAP_F_HARDWARE ; 
 int /*<<< orphan*/  CRYPTO_3DES_CBC ; 
 int /*<<< orphan*/  CRYPTO_AES_CBC ; 
 int /*<<< orphan*/  CRYPTO_ARC4 ; 
 int /*<<< orphan*/  CRYPTO_DES_CBC ; 
 int /*<<< orphan*/  CRYPTO_MD5 ; 
 int /*<<< orphan*/  CRYPTO_MD5_HMAC ; 
 int /*<<< orphan*/  CRYPTO_SHA1 ; 
 int /*<<< orphan*/  CRYPTO_SHA1_HMAC ; 
 int /*<<< orphan*/  DFS_DEVICE_SAE ; 
 int ENXIO ; 
 scalar_t__ PCI_DEVICE_ID_NLM_SAE ; 
 scalar_t__ bootverbose ; 
 scalar_t__ crypto_get_driverid (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 scalar_t__ crypto_register (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct xlp_sec_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  device_set_desc (int /*<<< orphan*/ ,char*) ; 
 int nlm_get_device_node (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nlm_get_sec_pcibase (int) ; 
 int nlm_qidstart (int /*<<< orphan*/ ) ; 
 int nlm_qnum (int /*<<< orphan*/ ) ; 
 int nlm_set_device_frequency (int,int /*<<< orphan*/ ,int) ; 
 scalar_t__ pci_get_device (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_get_slot (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*) ; 
 scalar_t__ xlp_sec_init (struct xlp_sec_softc*) ; 

__attribute__((used)) static int
xlp_sec_attach(device_t dev)
{
	struct xlp_sec_softc *sc = device_get_softc(dev);
	uint64_t base;
	int qstart, qnum;
	int freq, node;

	sc->sc_dev = dev;

	node = nlm_get_device_node(pci_get_slot(dev));
	freq = nlm_set_device_frequency(node, DFS_DEVICE_SAE, 250);
	if (bootverbose)
		device_printf(dev, "SAE Freq: %dMHz\n", freq);
	if(pci_get_device(dev) == PCI_DEVICE_ID_NLM_SAE) {
		device_set_desc(dev, "XLP Security Accelerator");
		sc->sc_cid = crypto_get_driverid(dev,
		    sizeof(struct xlp_sec_session), CRYPTOCAP_F_HARDWARE);
		if (sc->sc_cid < 0) {
			printf("xlp_sec - error : could not get the driver"
			    " id\n");
			goto error_exit;
		}
		if (crypto_register(sc->sc_cid, CRYPTO_DES_CBC, 0, 0) != 0)
			printf("register failed for CRYPTO_DES_CBC\n");

		if (crypto_register(sc->sc_cid, CRYPTO_3DES_CBC, 0, 0) != 0)
			printf("register failed for CRYPTO_3DES_CBC\n");

		if (crypto_register(sc->sc_cid, CRYPTO_AES_CBC, 0, 0) != 0)
			printf("register failed for CRYPTO_AES_CBC\n");

		if (crypto_register(sc->sc_cid, CRYPTO_ARC4, 0, 0) != 0)
			printf("register failed for CRYPTO_ARC4\n");

		if (crypto_register(sc->sc_cid, CRYPTO_MD5, 0, 0) != 0)
			printf("register failed for CRYPTO_MD5\n");

		if (crypto_register(sc->sc_cid, CRYPTO_SHA1, 0, 0) != 0)
			printf("register failed for CRYPTO_SHA1\n");

		if (crypto_register(sc->sc_cid, CRYPTO_MD5_HMAC, 0, 0) != 0)
			printf("register failed for CRYPTO_MD5_HMAC\n");

		if (crypto_register(sc->sc_cid, CRYPTO_SHA1_HMAC, 0, 0) != 0)
			printf("register failed for CRYPTO_SHA1_HMAC\n");

		base = nlm_get_sec_pcibase(node);
		qstart = nlm_qidstart(base);
		qnum = nlm_qnum(base);
		sc->sec_vc_start = qstart;
		sc->sec_vc_end = qstart + qnum - 1;
	}

	if (xlp_sec_init(sc) != 0)
		goto error_exit;
	if (bootverbose)
		device_printf(dev, "SEC Initialization complete!\n");
	return (0);

error_exit:
	return (ENXIO);

}