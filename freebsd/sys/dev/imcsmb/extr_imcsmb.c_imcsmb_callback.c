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
struct imcsmb_softc {int /*<<< orphan*/  imcsmb_pci; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int EINVAL ; 
 int SMB_DONTWAIT ; 
#define  SMB_RELEASE_BUS 129 
#define  SMB_REQUEST_BUS 128 
 struct imcsmb_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  imcsmb_pci_release_bus (int /*<<< orphan*/ ) ; 
 int imcsmb_pci_request_bus (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
imcsmb_callback(device_t dev, int index, void *data)
{
	struct imcsmb_softc *sc;
	int *how;
	int rc;

	sc = device_get_softc(dev);
	how = (int *) data;

	switch (index) {
	case SMB_REQUEST_BUS: {
		if (*how != SMB_DONTWAIT) {
			rc = EINVAL;
			goto out;
		}
		rc = imcsmb_pci_request_bus(sc->imcsmb_pci);
		break;
	}
	case SMB_RELEASE_BUS:
		imcsmb_pci_release_bus(sc->imcsmb_pci);
		rc = 0;
		break;
	default:
		rc = EINVAL;
		break;
	}

out:
	return (rc);
}