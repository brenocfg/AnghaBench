#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct image_hdr {int imageid; } ;
struct flash_file_hdr {char* build; int num_imgs; } ;
struct firmware {scalar_t__ data; } ;
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;
typedef  TYPE_1__* POCE_SOFTC ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,...) ; 
 int oce_sh_be3_flashdata (TYPE_1__*,struct firmware const*,int) ; 

__attribute__((used)) static int
oce_be3_fwupgrade(POCE_SOFTC sc, const struct firmware *fw)
{
	int rc = 0, num_imgs = 0, i = 0;
	const struct flash_file_hdr *fhdr;
	const struct image_hdr *img_ptr;

	fhdr = (const struct flash_file_hdr *)fw->data;
	if (fhdr->build[0] != '3') {
		device_printf(sc->dev, "Invalid BE3 firmware image\n");
		return EINVAL;
	}
	/* Display flash version */
	device_printf(sc->dev, "Flashing Firmware %s\n", &fhdr->build[2]);

	num_imgs = fhdr->num_imgs;
	for (i = 0; i < num_imgs; i++) {
		img_ptr = (const struct image_hdr *)((const char *)fw->data +
				sizeof(struct flash_file_hdr) +
				(i * sizeof(struct image_hdr)));
		if (img_ptr->imageid == 1) {
			rc = oce_sh_be3_flashdata(sc, fw, num_imgs);

			break;
		}
	}

	return rc;
}