#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct hdac_softc {int flags; int num_sdo; TYPE_1__* codecs; } ;
typedef  size_t nid_t ;
typedef  int /*<<< orphan*/  device_t ;
struct TYPE_2__ {uintptr_t vendor_id; uintptr_t device_id; uintptr_t revision_id; uintptr_t stepping_id; } ;

/* Variables and functions */
 int ENOENT ; 
 int HDAC_F_DMA_NOCACHE ; 
#define  HDA_IVAR_CODEC_ID 136 
#define  HDA_IVAR_DEVICE_ID 135 
#define  HDA_IVAR_DMA_NOCACHE 134 
#define  HDA_IVAR_REVISION_ID 133 
#define  HDA_IVAR_STEPPING_ID 132 
#define  HDA_IVAR_STRIPES_MASK 131 
#define  HDA_IVAR_SUBDEVICE_ID 130 
#define  HDA_IVAR_SUBVENDOR_ID 129 
#define  HDA_IVAR_VENDOR_ID 128 
 int /*<<< orphan*/  device_get_ivars (int /*<<< orphan*/ ) ; 
 struct hdac_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 uintptr_t pci_get_subdevice (int /*<<< orphan*/ ) ; 
 uintptr_t pci_get_subvendor (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
hdac_read_ivar(device_t dev, device_t child, int which, uintptr_t *result)
{
	struct hdac_softc *sc = device_get_softc(dev);
	nid_t cad = (uintptr_t)device_get_ivars(child);

	switch (which) {
	case HDA_IVAR_CODEC_ID:
		*result = cad;
		break;
	case HDA_IVAR_VENDOR_ID:
		*result = sc->codecs[cad].vendor_id;
		break;
	case HDA_IVAR_DEVICE_ID:
		*result = sc->codecs[cad].device_id;
		break;
	case HDA_IVAR_REVISION_ID:
		*result = sc->codecs[cad].revision_id;
		break;
	case HDA_IVAR_STEPPING_ID:
		*result = sc->codecs[cad].stepping_id;
		break;
	case HDA_IVAR_SUBVENDOR_ID:
		*result = pci_get_subvendor(dev);
		break;
	case HDA_IVAR_SUBDEVICE_ID:
		*result = pci_get_subdevice(dev);
		break;
	case HDA_IVAR_DMA_NOCACHE:
		*result = (sc->flags & HDAC_F_DMA_NOCACHE) != 0;
		break;
	case HDA_IVAR_STRIPES_MASK:
		*result = (1 << (1 << sc->num_sdo)) - 1;
		break;
	default:
		return (ENOENT);
	}
	return (0);
}