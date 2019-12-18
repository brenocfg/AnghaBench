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
typedef  size_t uint32_t ;
struct agp_amd64_softc {int n_mctrl; int /*<<< orphan*/  via_agp; int /*<<< orphan*/ * mctrl; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  AGP_AMD64_APCTRL ; 
 size_t AGP_AMD64_APCTRL_SIZE_MASK ; 
 size_t AGP_AMD64_TABLE_SIZE ; 
 int EINVAL ; 
 int agp_amd64_nvidia_set_aperture (int /*<<< orphan*/ ,size_t) ; 
 size_t* agp_amd64_table ; 
 int agp_amd64_uli_set_aperture (int /*<<< orphan*/ ,size_t) ; 
 int agp_amd64_via_set_aperture (int /*<<< orphan*/ ,size_t) ; 
 struct agp_amd64_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 size_t pci_cfgregread (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pci_cfgregwrite (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,size_t,int) ; 
 int pci_get_vendor (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
agp_amd64_set_aperture(device_t dev, uint32_t aperture)
{
	struct agp_amd64_softc *sc = device_get_softc(dev);
	uint32_t i;
	int j;

	for (i = 0; i < AGP_AMD64_TABLE_SIZE; i++)
		if (agp_amd64_table[i] == aperture)
			break;
	if (i >= AGP_AMD64_TABLE_SIZE)
		return (EINVAL);

	for (j = 0; j < sc->n_mctrl; j++)
		pci_cfgregwrite(0, sc->mctrl[j], 3, AGP_AMD64_APCTRL,
		    (pci_cfgregread(0, sc->mctrl[j], 3, AGP_AMD64_APCTRL, 4) &
		    ~(AGP_AMD64_APCTRL_SIZE_MASK)) | (i << 1), 4);

	switch (pci_get_vendor(dev)) {
	case 0x10b9:	/* ULi */
		return (agp_amd64_uli_set_aperture(dev, aperture));
		break;

	case 0x10de:	/* nVidia */
		return (agp_amd64_nvidia_set_aperture(dev, aperture));
		break;

	case 0x1106:	/* VIA */
		if (sc->via_agp)
			return (agp_amd64_via_set_aperture(dev, aperture));
		break;
	}

	return (0);
}