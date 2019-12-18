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
typedef  int uint8_t ;
struct firmware {int datasize; int /*<<< orphan*/  name; scalar_t__ data; } ;
struct bwi_softc {int /*<<< orphan*/  sc_dev; } ;
struct bwi_fwhdr {int fw_type; int fw_gen; int /*<<< orphan*/  fw_size; } ;

/* Variables and functions */
 int BWI_FW_GEN_1 ; 
 int BWI_FW_T_IV ; 
 int be32toh (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int,...) ; 

__attribute__((used)) static __inline int
bwi_fwimage_is_valid(struct bwi_softc *sc, const struct firmware *fw,
		     uint8_t fw_type)
{
	const struct bwi_fwhdr *hdr;

	if (fw->datasize < sizeof(*hdr)) {
		device_printf(sc->sc_dev,
		    "invalid firmware (%s): invalid size %zu\n",
		    fw->name, fw->datasize);
		return 0;
	}

	hdr = (const struct bwi_fwhdr *)fw->data;

	if (fw_type != BWI_FW_T_IV) {
		/*
		 * Don't verify IV's size, it has different meaning
		 */
		if (be32toh(hdr->fw_size) != fw->datasize - sizeof(*hdr)) {
			device_printf(sc->sc_dev,
			    "invalid firmware (%s): size mismatch, "
			    "fw %u, real %zu\n", fw->name,
			    be32toh(hdr->fw_size), fw->datasize - sizeof(*hdr));
			return 0;
		}
	}

	if (hdr->fw_type != fw_type) {
		device_printf(sc->sc_dev,
		    "invalid firmware (%s): type mismatch, "
		    "fw \'%c\', target \'%c\'\n", fw->name,
		    hdr->fw_type, fw_type);
		return 0;
	}

	if (hdr->fw_gen != BWI_FW_GEN_1) {
		device_printf(sc->sc_dev,
		    "invalid firmware (%s): wrong generation, "
		    "fw %d, target %d\n", fw->name, hdr->fw_gen, BWI_FW_GEN_1);
		return 0;
	}
	return 1;
}